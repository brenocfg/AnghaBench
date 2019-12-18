#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ wakeup_time; int h_idx; } ;
typedef  TYPE_1__ event_timer_t ;

/* Variables and functions */
 TYPE_1__** et_heap ; 
 int et_heap_size ; 

__attribute__((used)) static inline int basic_et_adjust (event_timer_t *et, int i) {
  int j;
  while (i > 1) {
    j = (i >> 1);
    if (et_heap[j]->wakeup_time <= et->wakeup_time) {
      break;
    }
    et_heap[i] = et_heap[j];
    et_heap[i]->h_idx = i;
    i = j;
  }
  j = 2*i;
  while (j <= et_heap_size) {
    if (j < et_heap_size && et_heap[j]->wakeup_time > et_heap[j+1]->wakeup_time) {
      j++;
    }
    if (et->wakeup_time <= et_heap[j]->wakeup_time) {
      break;
    }
    et_heap[i] = et_heap[j];
    et_heap[i]->h_idx = i;
    i = j;
    j <<= 1;
  }
  et_heap[i] = et;
  et->h_idx = i;
  return i;
}