#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double wakeup_time; } ;
struct conn_query {TYPE_3__ timer; struct conn_query* next; } ;
struct TYPE_4__ {struct conn_query* first_q; } ;
typedef  TYPE_1__ queue ;

/* Variables and functions */
 int /*<<< orphan*/  insert_event_timer (TYPE_3__*) ; 
 double precise_now ; 

int process_user_query_queue (queue *q) {
  struct conn_query *Q;
  double wtime = precise_now; //get_utime (CLOCK_MONOTONIC);// + 0.05;

  for (Q = q->first_q; Q != (struct conn_query *)q; Q = Q->next) {
    if (Q->timer.wakeup_time > wtime || Q->timer.wakeup_time == 0) {
      Q->timer.wakeup_time = wtime;
      insert_event_timer (&Q->timer);
    }
  }

  return 0;
}