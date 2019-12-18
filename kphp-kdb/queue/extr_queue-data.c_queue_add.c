#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* ev_last; TYPE_2__* ev_first; } ;
typedef  TYPE_1__ queue ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ event ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

inline void queue_add (queue *q, event *e) {
  assert (e->next == NULL);
  if (q->ev_first == NULL) {
    q->ev_first = q->ev_last = e;
  } else {
    q->ev_last->next = e;
    q->ev_last = e;
  }
}