#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ status; int /*<<< orphan*/  temp_id; int /*<<< orphan*/  declared_date; int /*<<< orphan*/  transaction_id; } ;
typedef  TYPE_1__ transaction_t ;
struct lev_money_trans_commit {int temp_id; int /*<<< orphan*/  transaction_id; } ;
typedef  scalar_t__ money_auth_code_t ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_MONEY_TRANS_COMMIT ; 
 struct lev_money_trans_commit* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int check_transaction (TYPE_1__*) ; 
 int commit_transaction (struct lev_money_trans_commit*) ; 
 int /*<<< orphan*/  compute_lock_codes (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  flush_binlog_forced (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_transaction (long long) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ trs_long_locked ; 

int do_long_commit_transaction (long long transaction_id, money_auth_code_t auth_code, char buffer[256]) {
  money_auth_code_t codes[2];
  transaction_t *T = get_transaction (transaction_id);
  if (!T) {
    return 0;
  }
  if (T->status != trs_long_locked) {
    return -1;
  }
  compute_lock_codes (T, codes);
  if (auth_code != codes[0]) {
    return -1;
  }
  int res = check_transaction (T);
  if (res < 0) {
    return res;
  }
  struct lev_money_trans_commit *EC = alloc_log_event (LEV_MONEY_TRANS_COMMIT, sizeof (struct lev_money_trans_commit), -2);

  EC->temp_id = -2;
  EC->transaction_id = T->transaction_id;

  assert (commit_transaction (EC) == 1);

  sprintf (buffer, "%16llx_%08x%08x", T->transaction_id, T->declared_date, T->temp_id);

  flush_binlog_forced (0);

  return 1;
}