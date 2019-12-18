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
struct TYPE_8__ {scalar_t__ status; int parties; TYPE_1__* T; scalar_t__ tr_cancel_peer; } ;
typedef  TYPE_3__ transaction_t ;
struct TYPE_9__ {int acc_state; long long balance; long long locked; TYPE_2__* acc_type; } ;
typedef  TYPE_4__ account_t ;
struct TYPE_7__ {int acc_class; } ;
struct TYPE_6__ {long long acc_incr; TYPE_4__* tr_account; } ;

/* Variables and functions */
 long long MAX_ACC_INCR ; 
 long long MAX_BALANCE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ trs_committed ; 

__attribute__((used)) static int check_cancellation_possibility (transaction_t *T) {
  int i;
  if (!T || T->status != trs_committed || T->tr_cancel_peer) {
    return -1;
  }
  for (i = 0; i < T->parties; i++) {
    long long x = -T->T[i].acc_incr;
    account_t *A = T->T[i].tr_account;
    if (!A) {
      return -32 + i;
    }
    int c = A->acc_type->acc_class;
    if (x >= 0) {
      assert (x < MAX_ACC_INCR);
      if ((A->acc_state & 1) || (c & 1)) {
        return -32 + i;
      }
      if (A->balance + x >= MAX_BALANCE) {
        return -1;
      }
    } else {
      assert (x >= -MAX_ACC_INCR);
      if ((A->acc_state & 2) || (c & 2)) {
        return -32 + i;
      }
      if (A->balance + x < A->locked && !(c & 4)) {
        return -48 + i;
      }
      if (A->balance + x < -MAX_BALANCE || A->locked - x >= MAX_BALANCE) {
        return -1;
      }
    }
  }
  return 1;
}