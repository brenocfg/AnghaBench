#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fd; int in_queue; } ;
typedef  TYPE_1__ event_t ;

/* Variables and functions */
 TYPE_1__* Events ; 
 int MAX_EVENTS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ cmp_ev (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__** ev_heap ; 
 int ev_heap_size ; 
 int remove_event_from_heap (TYPE_1__*,int) ; 

int put_event_into_heap (event_t *ev) {
  int v = ev->fd, i, j;
  event_t *x;
  assert (v >= 0 && v < MAX_EVENTS && Events + v == ev);
  i = ev->in_queue ? remove_event_from_heap (ev, 1) : ++ev_heap_size;
  assert (i <= MAX_EVENTS);
  while (i > 1) {
    j = (i >> 1);
    x = ev_heap[j];
    if (cmp_ev(x,ev) <= 0) break;
    ev_heap[i] = x;
    x->in_queue = i;
    i = j;
  }
  ev_heap[i] = ev;
  ev->in_queue = i;
  return i;
}