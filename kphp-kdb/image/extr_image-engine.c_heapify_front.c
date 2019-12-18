#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct forth_request {scalar_t__ priority; } ;

/* Variables and functions */
 struct forth_request** HEAP ; 
 int queue_size ; 

__attribute__((used)) static inline void heapify_front (struct forth_request *E, int i) {
  while (1) {
    int j = i << 1;
    if (j > queue_size) { break; }
    if (j < queue_size && HEAP[j]->priority > HEAP[j+1]->priority) {
      j++;
    }
    if (E->priority <= HEAP[j]->priority) { break; }
    HEAP[i] = HEAP[j];
    i = j;
  }
  HEAP[i] = E;
}