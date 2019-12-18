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
struct TYPE_4__ {scalar_t__ status; scalar_t__ long_lock_cancel_timeout; int /*<<< orphan*/  long_lock_secret; } ;
typedef  TYPE_1__ transaction_t ;
typedef  scalar_t__ money_auth_code_t ;

/* Variables and functions */
 scalar_t__ LONG_LOCK_CANCEL_TIMEOUT ; 
 int /*<<< orphan*/  compute_lock_codes (TYPE_1__*,scalar_t__*) ; 
 TYPE_1__* get_transaction (long long) ; 
 scalar_t__ now ; 
 scalar_t__ trs_cancelled ; 
 scalar_t__ trs_committed ; 
 scalar_t__ trs_long_locked ; 

int long_check_transaction (long long transaction_id, money_auth_code_t auth_code) {
  money_auth_code_t codes[2];
  transaction_t *T = get_transaction (transaction_id);
  if (!T) {
    return 0;
  }
  if (T->status != trs_cancelled && T->status != trs_long_locked && T->status != trs_committed) {
    return 0;
  }
  if (!T->long_lock_secret) {
    return -1;
  }
  compute_lock_codes (T, codes);
  if (auth_code != codes[0] && auth_code != codes[1]) {
    return -1;
  }
  if (T->status == trs_committed) {
    return 1;
  }
  if (T->status == trs_cancelled) {
    return 3;
  }
  if (auth_code == codes[0]) {
    T->long_lock_cancel_timeout = now + LONG_LOCK_CANCEL_TIMEOUT;
  }
  return 2;
}