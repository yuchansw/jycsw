#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * 소프트웨어학부
 * 20240402017
 * 공예준
 */

// 배열 출력
void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 삽입 정렬
void insertionSort(int* arr, int n) {
    // 인덱스 0은 이미 정렬되어 있다고 가정하고 시작
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        // key보다 큰 원소들을 오른쪽으로 이동
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int* arr, int left, int mid, int right) {
    int fIdx = left;
    int rIdx = mid + 1;
    int sIdx = left;
    int* sortArr = (int*)malloc(sizeof(int) * (right + 1)); // 정렬된 배열을 저장할 임시 배열

    // 병합할 두 영역의 데이터를 비교하여 배열 sortArr에 저장
    while (fIdx <= mid && rIdx <= right) {
        // 두 영역의 데이터 중 작은 데이터를 선택하여 sortArr에 저장
        if (arr[fIdx] <= arr[rIdx]) {
            sortArr[sIdx] = arr[fIdx++];
        } else {
            sortArr[sIdx] = arr[rIdx++];
        }
        sIdx++;
    }


    // 배열 arr의 앞부분이 모두 sortArr에 저장되었을 경우 뒷부분에 남은 데이터를 sortArr에 저장
    if (fIdx > mid) {
        for (int i = rIdx; i <= right; i++, sIdx++) {
            sortArr[sIdx] = arr[i];
        }
    }
    // 배열 arr의 뒷부분이 모두 sortArr에 저장되었을 경우 앞부분에 남은 데이터를 sortArr에 저장
    else {
        for (int i = fIdx; i <= mid; i++, sIdx++) {
            sortArr[sIdx] = arr[i];
        }
    }
    // 병합 결과를 옮겨 담기
    for (int i = left; i <= right; i++) {
        arr[i] = sortArr[i];
    }
    free(sortArr);
}

/**
 * 병합 정렬(재귀)
 * 분할 과정이 재귀적
 */
void mergeSortRecursive(int* arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2; // 배열의 중간 인덱스

        mergeSortRecursive(arr, left, mid); // 중간 인덱스 기준 왼쪽 부분 배열 정렬
        mergeSortRecursive(arr, mid + 1, right); // 중간 인덱스 기준 오른쪽 부분 배열 정렬

        merge(arr, left, mid, right); // 정렬된 두 부분 배열 병합
    }
}

/**
 * 병합 정렬(반복)
 * 분할 과정이 반복문을 통해 수행
 */
void mergeSortIterative(int* arr, int n) {
    int* sortArr = (int*)malloc(sizeof(int) * n); // 정렬된 배열을 저장할 임시 배열
    int left, mid, right;

    // 사이즈가 1, 2, 4, 8, ... 순으로 증가
    for (int size = 1; size < n; size *= 2) {
        left = 0;
        // 사이즈가 size인 두 배열을 병합
        while (left + size < n) {
            mid = left + size - 1;
            right = mid + size;
            // 배열의 끝을 넘어가는 경우
            if (right >= n) {
                right = n - 1;
            }
            merge(arr, left, mid, right);
            left = right + 1;
        }
    }
    free(sortArr);
}

int main(void) {
    srand(time(NULL));
    int arr[10], arr2[100], arr3[1000]; // 배열 선언
    int copy[10], copy2[100], copy3[1000]; // 배열 복사본
    int n = sizeof(arr) / sizeof(arr[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    clock_t start, end;
    double duration;

    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 11;
    }
    for (int i = 0; i < 100; i++) {
        arr2[i] = rand() % 101;
    }
    for (int i = 0; i < 1000; i++) {
        arr3[i] = rand() % 1001;
    }

    // copy에 arr 배열 복사
    memcpy(copy, arr, sizeof(arr));
    memcpy(copy2, arr2, sizeof(arr2));
    memcpy(copy3, arr3, sizeof(arr3));

    printf("size: 10\n삽입 정렬 전:\n");
    printArray(copy, n);
    start = clock();
    insertionSort(copy, n);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC; // (종료지점 시간 - 시작지점 시간) / 초당 틱 수
    printf("삽입 정렬 후:\n");
    printArray(copy, n);
    printf("%d개 요소 삽입 정렬하는데 걸린 시간: %f\n\n", n, duration);

    printf("size: 100\n삽입 정렬 전:\n");
    printArray(copy2, n2);
    start = clock();
    insertionSort(copy2, n2);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("삽입 정렬 후:\n");
    printArray(copy2, n2);
    printf("%d개 요소 삽입 정렬하는데 걸린 시간: %f\n\n", n2, duration);

    printf("size: 1000\n삽입 정렬 전:\n");
    printArray(copy3, n3);
    start = clock();
    insertionSort(copy3, n3);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("삽입 정렬 후:\n");
    printArray(copy3, n3);
    printf("%d개 요소 삽입 정렬하는데 걸린 시간: %f\n\n\n\n", n3, duration);

    memcpy(copy, arr, sizeof(arr));
    memcpy(copy2, arr2, sizeof(arr2));
    memcpy(copy3, arr3, sizeof(arr3));

    printf("size: 10\n병합 정렬(재귀) 전:\n");
    printArray(copy, n);
    start = clock();
    mergeSortRecursive(copy, 0, n - 1);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("병합 정렬(재귀) 후:\n");
    printArray(copy, n);
    printf("%d개 요소 병합 정렬(재귀)하는데 걸린 시간: %f\n\n", n, duration);

    printf("size: 100\n병합 정렬(재귀) 전:\n");
    printArray(copy2, n2);
    start = clock();
    mergeSortRecursive(copy2, 0, n2 - 1);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("병합 정렬(재귀) 후:\n");
    printArray(copy2, n2);
    printf("%d개 요소 병합 정렬(재귀)하는데 걸린 시간: %f\n\n", n2, duration);

    printf("size: 1000\n병합 정렬(재귀) 전:\n");
    printArray(copy3, n3);
    start = clock();
    mergeSortRecursive(copy3, 0, n3 - 1);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("병합 정렬(재귀) 후:\n");
    printArray(copy3, n3);
    printf("%d개 요소 병합 정렬(재귀)하는데 걸린 시간: %f\n\n\n\n", n3, duration);

    memcpy(copy, arr, sizeof(arr));
    memcpy(copy2, arr2, sizeof(arr2));
    memcpy(copy3, arr3, sizeof(arr3));

    printf("size: 10\n병합 정렬(반복) 전:\n");
    printArray(copy, n);
    start = clock();
    mergeSortIterative(copy, n);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("병합 정렬(반복) 후:\n");
    printArray(copy, n);
    printf("%d개 요소 병합 정렬(반복)하는데 걸린 시간: %f\n\n", n, duration);

    printf("size: 100\n병합 정렬(반복) 전:\n");
    printArray(copy2, n2);
    start = clock();
    mergeSortIterative(copy2, n2);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("병합 정렬(반복) 후:\n");
    printArray(copy2, n2);
    printf("%d개 요소 병합 정렬(반복)하는데 걸린 시간: %f\n\n", n2, duration);

    printf("size: 1000\n병합 정렬(반복) 전:\n");
    printArray(copy3, n3);
    start = clock();
    mergeSortIterative(copy3, n3);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("병합 정렬(반복) 후:\n");
    printArray(copy3, n3);
    printf("%d개 요소 병합 정렬(반복)하는데 걸린 시간: %f\n\n\n\n", n3, duration);
}

