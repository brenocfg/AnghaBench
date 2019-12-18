#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct event_timer {int dummy; } ;
struct binlog_wait_query {int /*<<< orphan*/  (* on_alarm ) (struct binlog_wait_query*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct binlog_wait_query*) ; 
 int /*<<< orphan*/  zfree (struct binlog_wait_query*,int) ; 

int tl_binlog_wait_pos_alarm (struct event_timer *ev) {
 
  struct binlog_wait_query *Q = (void *)ev;
  //fprintf (stderr, "delete: Q = %p\n", Q);
  //binlog_wait_tree = tree_delete_binlog_wait (binlog_wait_tree, Q);
  Q->on_alarm (Q);
  zfree (Q, sizeof (*Q));
  return 0;
}