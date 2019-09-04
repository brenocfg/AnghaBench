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
struct tl_saved_query {int /*<<< orphan*/  failed; int /*<<< orphan*/  wait_num; } ;
struct binlog_wait_query {scalar_t__ timeout; scalar_t__ start_time; int /*<<< orphan*/  wait_pos; int /*<<< orphan*/  ev; struct tl_saved_query* extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_finished_query (struct tl_saved_query*) ; 
 int /*<<< orphan*/  assert (int) ; 
 long long log_last_pos () ; 
 long long lookup_binlog_time (int /*<<< orphan*/ ) ; 
 scalar_t__ precise_now ; 
 int /*<<< orphan*/  remove_event_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tl_binlog_wait_pos_add (struct tl_saved_query*,long long,scalar_t__) ; 

void tl_binlog_wait_time_on_complete (struct binlog_wait_query *Q) {
  struct tl_saved_query *q = Q->extra;
  remove_event_timer (&Q->ev);
  q->wait_num --;
  long long pos = lookup_binlog_time (Q->wait_pos);
  assert (pos > 0);
  if (log_last_pos () < pos && !q->failed) {
    tl_binlog_wait_pos_add (q, pos, Q->start_time + Q->timeout - precise_now);
  }

  if (!q->wait_num && !q->failed) {
    add_finished_query (q);
  }
}