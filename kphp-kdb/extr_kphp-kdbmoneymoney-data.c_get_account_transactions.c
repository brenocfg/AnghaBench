#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ money_auth_code_t ;
struct TYPE_5__ {scalar_t__ access_code; scalar_t__ withdraw_code; int trans_num; int /*<<< orphan*/ * acc_transactions; TYPE_1__* acc_type; } ;
typedef  TYPE_2__ account_t ;
struct TYPE_4__ {scalar_t__ access_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* get_account (int,long long) ; 
 int /*<<< orphan*/  store_transaction_short (long long**,int /*<<< orphan*/ ,int) ; 

int get_account_transactions (int acc_type_id, long long acc_id, int flags, int from, int to, money_auth_code_t auth_code, long long *R, int *R_cnt, int R_size) {
  account_t *A = get_account (acc_type_id, acc_id);
  int N, i;
  long long *RR = R, *R_end;
  if (!A) {
    return -1;
  }
  if (A->access_code && A->access_code != auth_code && A->withdraw_code != auth_code && !(A->acc_type->access_code == auth_code && auth_code)) {
    return -1;
  }
  N = A->trans_num;
  assert (N >= 0);
  *R_cnt = 0;
  if (!from || !to || !N) {
    return N;
  }
  if (from < 0) {
    from += N;
  } else {
    from--;
  }
  if (to < 0) {
    to += N;
  } else {
    to--;
  }

  if (from >= N) {
    from = N - 1;
  }
  if (to >= N) {
    to = N - 1;
  }

  if (from < 0) {
    from = 0;
  }
  if (to < 0) {
    to = 0;
  }

  R_end = R + (R_size - 16);

  if (from <= to) {
    for (i = from; i <= to && R <= R_end; i++) {
      store_transaction_short (&R, A->acc_transactions[i], flags);
    }
  } else {
    for (i = from; i >= to && R <= R_end; i--) {
      store_transaction_short (&R, A->acc_transactions[i], flags);
    }
  }
  *R_cnt = R - RR;
  return N;
}