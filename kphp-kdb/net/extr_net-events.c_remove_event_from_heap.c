#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int fd; int in_queue; } ;
typedef  TYPE_1__ event_t ;

/* Variables and functions */
 TYPE_1__* Events ; 
 int MAX_EVENTS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ cmp_ev (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__** ev_heap ; 
 int ev_heap_size ; 

int remove_event_from_heap (event_t *ev, int allow_hole) {
  int v = ev->fd, i, j, N = ev_heap_size;
  event_t *x;
  assert (v >= 0 && v < MAX_EVENTS && Events + v == ev);
  i = ev->in_queue;
  if (!i) return 0;
  assert (i > 0 && i <= N);
  ev->in_queue = 0;
  do {
    j = (i << 1);
    if (j > N) break;
    if (j < N && cmp_ev(ev_heap[j+1], ev_heap[j]) < 0) j++;
    ev_heap[i] = x = ev_heap[j];
    x->in_queue = i;
    i = j;
  } while(1);
  if (allow_hole) {
    ev_heap[i] = 0;
    return i;
  }
  if (i < N) {
    ev = ev_heap[N];
    ev_heap[N] = 0;
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
  }
  ev_heap_size--;
  return N;
}