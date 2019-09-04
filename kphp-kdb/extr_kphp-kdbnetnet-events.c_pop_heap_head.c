#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int in_queue; } ;
typedef  TYPE_1__ event_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ cmp_ev (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__** ev_heap ; 
 int ev_heap_size ; 

event_t *pop_heap_head (void) {
  int i, j, N = ev_heap_size;
  event_t *ev, *x, *y;
  if (!N) return 0;
  ev = ev_heap[1];
  assert (ev && ev->in_queue == 1);
  ev->in_queue = 0;
  if (!--ev_heap_size) return ev;
  x = ev_heap[N--];
  i = 1;
  while (1) {
    j = (i << 1);
    if (j > N) break;
    if (j < N && cmp_ev(ev_heap[j], ev_heap[j+1]) > 0) j++;
    y = ev_heap[j];
    if (cmp_ev(x, y) <= 0) break;
    ev_heap[i] = y;
    y->in_queue = i;
    i = j;
  } 
  ev_heap[i] = x;
  x->in_queue = i;
  return ev;
}