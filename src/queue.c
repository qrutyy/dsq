#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

struct Queue {
    int32_t head, size, tail;
    uint32_t capacity;
    int32_t* array;
};

struct Queue* create_queue(uint32_t current_capacity) {
    struct Queue* new_queue = malloc(sizeof(struct Queue));
    if (new_queue == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_queue->capacity = current_capacity;
    new_queue->head = new_queue->size = 0;
    new_queue->tail = current_capacity - 1;
    new_queue->size = 0;
    new_queue->array = calloc(current_capacity, sizeof(int32_t));
    if (new_queue->array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return new_queue;
}

bool is_queue_full(struct Queue* current_queue) {
    return current_queue->size == current_queue->capacity;
}

bool is_queue_empty(struct Queue* current_queue) {
    return current_queue->size == 0;
}

void push_queue(struct Queue* current_queue, int32_t value) {
    if (is_queue_full(current_queue)) {
        current_queue->capacity *= 2;
        current_queue->array = realloc(current_queue->array, current_queue->capacity);
        if (current_queue->array == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    current_queue->tail = (current_queue->tail + 1) % current_queue->capacity;
    current_queue->array[current_queue->tail] = value;
    current_queue->size++;
}

int32_t pop_queue(struct Queue* current_queue) {
    if (is_queue_empty(current_queue)) {
        fprintf(stderr, "Current queue is empty\n");
        return INT32_MIN;
    }
    int32_t value = current_queue->array[current_queue->head];
    current_queue->head = (current_queue->head + 1) % current_queue->capacity;
    current_queue->size--;
    return value;
}

int32_t peek_queue_head(struct Queue* current_queue) {
    if (is_queue_empty(current_queue)) {
        fprintf(stderr, "Current queue is empty\n");
        return INT32_MIN;
    }
    return current_queue->array[current_queue->head];
}

int32_t peek_queue_tail(struct Queue* current_queue) {
    if (is_queue_empty(current_queue)) {
        fprintf(stderr, "Current queue is empty\n");
        return INT32_MIN;
    }
    return current_queue->array[current_queue->tail];
}

void free_queue(struct Queue* current_queue) {
    free(current_queue);
}