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
struct TYPE_6__ {scalar_t__ status; int locked_until; struct TYPE_6__* unlock_next; } ;
typedef  TYPE_1__ transaction_t ;

/* Variables and functions */
 int DELAY_QUEUES ; 
 TYPE_1__** DelayQueues ; 
 int /*<<< orphan*/  assert (int) ; 
 int check_transaction (TYPE_1__*) ; 
 int dq ; 
 int /*<<< orphan*/  flush_binlog_forced (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_temp_transaction (int) ; 
 int lock_transaction (TYPE_1__*) ; 
 scalar_t__ trs_temp ; 
 scalar_t__ trs_temp_locked ; 

int do_lock_transaction (int temp_id) {
  transaction_t *T = get_temp_transaction (temp_id);
  if (!T) {
    return 0;
  }
  int res = check_transaction (T);
  if (res < 0) {
    return res;
  }
  if (T->status != trs_temp) {
    return 0;
  }
  if (!T->locked_until) {
    assert (!T->unlock_next);
    T->unlock_next = DelayQueues[(dq + 15) & (DELAY_QUEUES-1)];
    DelayQueues[(dq + 15) & (DELAY_QUEUES-1)] = T;
  }
  if (T->locked_until < dq + 15) {
    T->locked_until = dq + 15;
  }

  assert (lock_transaction (T) == 1);
  T->status = trs_temp_locked;

  flush_binlog_forced (0);

  return 2;
}