#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {double wakeup_time; } ;
struct conn_query {TYPE_4__ timer; } ;
struct TYPE_6__ {int n; TYPE_1__** k; } ;
typedef  TYPE_2__ qkey_group ;
struct TYPE_5__ {struct conn_query* conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  insert_event_timer (TYPE_4__*) ; 
 double precise_now ; 

void release_key_group (qkey_group *k) {
  int i;
  for (i = 0; i < k->n; i++) {
    if (k->k[i] != NULL) {
      struct conn_query *Q = k->k[i]->conn;
      if (Q != NULL) {
        double wtime = precise_now; //get_utime (CLOCK_MONOTONIC);// + 0.01;

        if (Q->timer.wakeup_time > wtime || Q->timer.wakeup_time == 0) {
          Q->timer.wakeup_time = wtime;
          insert_event_timer (&Q->timer);
        }
      }
    }
  }
}