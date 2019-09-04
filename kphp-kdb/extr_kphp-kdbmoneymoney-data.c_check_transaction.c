#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int status; int parties; TYPE_2__* T; } ;
typedef  TYPE_3__ transaction_t ;
struct TYPE_9__ {int acc_state; long long balance; scalar_t__ withdraw_code; scalar_t__ lock_num; long long locked; TYPE_1__* acc_type; } ;
typedef  TYPE_4__ account_t ;
struct TYPE_7__ {long long acc_incr; scalar_t__ auth_code; TYPE_4__* tr_account; } ;
struct TYPE_6__ {int acc_class; } ;

/* Variables and functions */
 long long MAX_ACC_INCR ; 
 long long MAX_BALANCE ; 
 int /*<<< orphan*/  assert (int) ; 
 int trs_declared_locked ; 
 int trs_long_locked ; 

__attribute__((used)) static int check_transaction (transaction_t *T) {
  int i, c;
  assert (T->status <= trs_declared_locked || T->status == trs_long_locked);
  for (i = 0; i < T->parties; i++) {
    long long x = T->T[i].acc_incr;
    account_t *A = T->T[i].tr_account;
    if (!A) {
      return -32 + i;
    }
//    assert (x);
    c = A->acc_type->acc_class;
    // main idea: 0 is negative (withdrawal operation) 
    if (x > 0) {
      assert (x < MAX_ACC_INCR);
      if ((A->acc_state & 2) || (c & 2)) {
        return -32 + i;
      }
      if (A->balance + x >= MAX_BALANCE) {
        return -1;
      }
    } else {
      assert (x >= -MAX_ACC_INCR);
      if ((A->acc_state & 1) || (c & 1)) {
        return -32 + i;
      }
      if (T->status != trs_long_locked && A->withdraw_code && T->T[i].auth_code != A->withdraw_code) {
        return -32 + i;
      }
      if (T->status & 1) {
        assert (A->lock_num > 0 && A->locked + x >= 0);
        assert (A->balance >= A->locked || (c & 4));
      } else {
        if (A->balance + x < A->locked && !(c & 4)) {
          return -48+i;
        }
      }
      if (A->balance + x < -MAX_BALANCE || A->locked - x >= MAX_BALANCE) {
        return -1;
      }
    }
  }
  return 0;
}