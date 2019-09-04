#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ status; scalar_t__ long_lock_cancel_timeout; int /*<<< orphan*/  transaction_id; } ;
typedef  TYPE_1__ transaction_t ;
struct lev_money_trans_cancel {int temp_id; int /*<<< orphan*/  transaction_id; } ;
typedef  scalar_t__ money_auth_code_t ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_MONEY_TRANS_CANCEL ; 
 struct lev_money_trans_cancel* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int cancel_transaction (struct lev_money_trans_cancel*) ; 
 int /*<<< orphan*/  compute_lock_codes (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  flush_binlog_forced (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_transaction (long long) ; 
 scalar_t__ now ; 
 scalar_t__ trs_long_locked ; 

int do_long_cancel_transaction (long long transaction_id, money_auth_code_t auth_code) {
  money_auth_code_t codes[2];
  transaction_t *T = get_transaction (transaction_id);
  if (!T) {
    return 0;
  }
  if (T->status != trs_long_locked) {
    return -1;
  }
  compute_lock_codes (T, codes);
  if (auth_code != codes[0] && (auth_code != codes[1] || now < T->long_lock_cancel_timeout)) {
    return -1;
  }
  struct lev_money_trans_cancel *EC = alloc_log_event (LEV_MONEY_TRANS_CANCEL, sizeof (struct lev_money_trans_cancel), -2);

  EC->temp_id = (auth_code == codes[0] ? -2 : -1);
  EC->transaction_id = T->transaction_id;

  assert (cancel_transaction (EC) == 1);

  flush_binlog_forced (0);

  return 3;
}