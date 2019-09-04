#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ h_idx; } ;
struct conn_query {scalar_t__ req_generation; TYPE_3__ timer; TYPE_2__* requester; TYPE_1__* outbound; } ;
struct TYPE_8__ {int /*<<< orphan*/  in_queue; } ;
struct TYPE_6__ {scalar_t__ generation; TYPE_4__* ev; int /*<<< orphan*/  fd; int /*<<< orphan*/  pending_queries; } ;
struct TYPE_5__ {int fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_event_into_heap (TYPE_4__*) ; 
 int /*<<< orphan*/  remove_event_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

int delete_conn_query_from_requester (struct conn_query *q) {
  vkprintf (2, "delete_conn_query_from_requester (%p)\n", q);
  if (q->requester && q->requester->generation == q->req_generation) {
    if (!--q->requester->pending_queries) {
      /* wake up master */
      vkprintf (2, "socket %d was the last one, waking master %d\n", q->outbound ? q->outbound->fd : -1, q->requester->fd);
      if (!q->requester->ev->in_queue) {
        put_event_into_heap (q->requester->ev);
      }
    }
  }
  q->requester = 0;
  if (q->timer.h_idx) {
    remove_event_timer (&q->timer);
  }
  return 0;
}