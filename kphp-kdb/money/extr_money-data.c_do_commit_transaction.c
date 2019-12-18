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
struct TYPE_6__ {scalar_t__ status; long long transaction_id; int /*<<< orphan*/  temp_id; int /*<<< orphan*/  declared_date; } ;
typedef  TYPE_1__ transaction_t ;
struct lev_money_trans_commit {long long transaction_id; int /*<<< orphan*/  temp_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_MONEY_TRANS_COMMIT ; 
 int /*<<< orphan*/  add_temp_transaction (TYPE_1__*) ; 
 struct lev_money_trans_commit* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int check_transaction (TYPE_1__*) ; 
 int commit_transaction (struct lev_money_trans_commit*) ; 
 int do_declare_transaction (TYPE_1__*) ; 
 int /*<<< orphan*/  flush_binlog_forced (int /*<<< orphan*/ ) ; 
 long long get_next_transaction_id () ; 
 TYPE_1__* get_temp_transaction (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ trs_temp ; 
 scalar_t__ trs_temp_locked ; 

int do_commit_transaction (int temp_id, long long *transaction_id, char buffer[256]) {
  transaction_t *T = get_temp_transaction (temp_id);
  *transaction_id = 0;
  *buffer = 0;
  if (!T) {
    return 0;
  }
  int res = check_transaction (T);
  if (res < 0) {
    return res;
  }
  if (T->status != trs_temp && T->status != trs_temp_locked) {
    return -1;
  }
  if (!T->transaction_id) {
    T->transaction_id = get_next_transaction_id();
  }

  assert (do_declare_transaction (T) == 1);

  struct lev_money_trans_commit *EC = alloc_log_event (LEV_MONEY_TRANS_COMMIT, sizeof (struct lev_money_trans_commit), temp_id);

  EC->temp_id = T->temp_id;
  EC->transaction_id = T->transaction_id;

  assert (commit_transaction (EC) == 1);

  add_temp_transaction (T);

  *transaction_id = T->transaction_id;

  sprintf (buffer, "%16llx_%08x%08x", T->transaction_id, T->declared_date, T->temp_id);

  flush_binlog_forced (0);

  return 1;
}