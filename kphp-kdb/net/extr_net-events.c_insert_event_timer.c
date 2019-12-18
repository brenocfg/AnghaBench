#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int h_idx; } ;
typedef  TYPE_1__ event_timer_t ;

/* Variables and functions */
 int MAX_EVENT_TIMERS ; 
 int /*<<< orphan*/  assert (int) ; 
 int basic_et_adjust (TYPE_1__*,int) ; 
 TYPE_1__** et_heap ; 
 int et_heap_size ; 

int insert_event_timer (event_timer_t *et) {
  int i;
  if (et->h_idx) {
    i = et->h_idx;
    assert (i > 0 && i <= et_heap_size && et_heap[i] == et);
  } else {
    assert (et_heap_size < MAX_EVENT_TIMERS);
    i = ++et_heap_size;
  }
  return basic_et_adjust (et, i);
}