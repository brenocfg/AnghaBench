#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ wakeup_time; int /*<<< orphan*/  wakeup; scalar_t__ h_idx; } ;
struct conn_query {TYPE_1__ timer; TYPE_2__* requester; int /*<<< orphan*/  req_generation; struct conn_query* prev; struct conn_query* next; } ;
struct TYPE_4__ {int /*<<< orphan*/  pending_queries; int /*<<< orphan*/  generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  conn_event_wakeup_gateway ; 
 int /*<<< orphan*/  insert_event_timer (TYPE_1__*) ; 

int insert_conn_query_into_list (struct conn_query *q, struct conn_query *h) {
  q->next = h;
  q->prev = h->prev;
  h->prev->next = q;
  h->prev = q;
  assert (q->requester);
  q->req_generation = q->requester->generation;
  q->requester->pending_queries++;
  q->timer.h_idx = 0;
  q->timer.wakeup = conn_event_wakeup_gateway;
  if (q->timer.wakeup_time > 0) {
    insert_event_timer (&q->timer);
  }
  return 0;
}