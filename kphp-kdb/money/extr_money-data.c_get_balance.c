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
struct TYPE_5__ {scalar_t__ access_code; long long locked; long long balance; TYPE_1__* acc_type; } ;
typedef  TYPE_2__ account_t ;
struct TYPE_4__ {int currency; } ;

/* Variables and functions */
 long long BALANCE_NO_ACCOUNT ; 
 long long ERROR_BALANCE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,long long) ; 
 TYPE_2__* get_account (int,long long) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

long long get_balance (int acc_type_id, long long acc_id, money_auth_code_t auth_code, int *currency, long long *locked) {
  if (verbosity > 1) {
    fprintf (stderr, "in get_balance(%d,%lld)\n", acc_type_id, acc_id);
  }

  account_t *A = get_account (acc_type_id, acc_id);
  if (!A) {
    return BALANCE_NO_ACCOUNT;
  }

  if (A->access_code && auth_code != A->access_code) {
    return ERROR_BALANCE;
  }

  *currency = A->acc_type->currency;
  *locked = A->locked;

  return A->balance;
}