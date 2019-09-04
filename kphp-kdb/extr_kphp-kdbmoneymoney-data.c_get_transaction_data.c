#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ status; int parties; long long created_at; long long long_locked_until; long long long_lock_cancel_timeout; long long ip; char* comment; TYPE_3__* T; TYPE_1__* tr_cancel_peer; } ;
typedef  TYPE_4__ transaction_t ;
struct TYPE_12__ {long long acc_id; TYPE_2__* acc_type; int /*<<< orphan*/  withdraw_code; int /*<<< orphan*/  access_code; } ;
typedef  TYPE_5__ account_t ;
struct TYPE_10__ {long long acc_incr; TYPE_5__* tr_account; } ;
struct TYPE_9__ {long long acc_type_id; long long currency; int /*<<< orphan*/  withdraw_code; int /*<<< orphan*/  access_code; } ;
struct TYPE_8__ {long long transaction_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_5__*) ; 
 scalar_t__ check_signature (char*,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* get_transaction (long long) ; 
 int sprintf (char*,char*,long long,int) ; 
 long long trs_deleting ; 
 scalar_t__ trs_temp_locked ; 

int get_transaction_data (long long transaction_id, int sign_time, char auth_signature[32], long long *R, int *R_cnt, char **comment) {
  transaction_t *T = get_transaction (transaction_id);
  int i, N, L, ok;
  static char temp[128];
  if (!T) {
    return -1;
  }
  if (T->status <= trs_temp_locked) {
    return -1;
  }
  L = sprintf (temp, "%lld,%d", transaction_id, sign_time);
  N = T->parties;
  ok = 0;
  for (i = 0; i < N; i++) {
    account_t *A = T->T[i].tr_account;
    assert (A);
    if (!A->access_code 
     || check_signature (auth_signature, temp, L, A->access_code) || check_signature (auth_signature, temp, L, A->withdraw_code) 
     || check_signature (auth_signature, temp, L, A->acc_type->access_code) || check_signature (auth_signature, temp, L, A->acc_type->withdraw_code)) {
      ok = 1;
      break;
    }
  }
  if (!ok) {
    return -1;
  }
  R[0] = trs_deleting - T->status;
  R[1] = T->created_at;
  R[2] = T->long_locked_until;
  R[3] = T->long_lock_cancel_timeout;
  R[4] = T->ip;
  R[5] = T->tr_cancel_peer ? T->tr_cancel_peer->transaction_id : 0;
  R[6] = R[7] = 0;
  R += 8;
  for (i = 0; i < N; i++) {
    R[0] = T->T[i].tr_account->acc_type->acc_type_id;
    R[1] = T->T[i].tr_account->acc_id;
    R[2] = T->T[i].acc_incr;
    R[3] = T->T[i].tr_account->acc_type->currency;
    R += 4;
  }
  *R_cnt = 8 + 4*N;
  *comment = T->comment;

  return N;
}