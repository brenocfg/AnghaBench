#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lev_copyexec_aux_transaction_cmd_wait {int transaction_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_COPYEXEC_AUX_TRANSACTION_CMD_CANCEL ; 
 int /*<<< orphan*/  T ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 struct lev_copyexec_aux_transaction_cmd_wait* tb_alloc_logevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int transactions ; 

__attribute__((used)) static int cancel_transaction (int transaction_id) {
  if (transaction_id < 1) {
    kprintf ("cancel_transaction: X < 1\n");
    return -1;
  }
  if (transaction_id >= transactions + 1) {
    kprintf ("cancel_transaction: X >= current transaction id (X = %d, transaction_id = %d)\n", transaction_id, transactions + 1);
    return -2;
  }
  struct lev_copyexec_aux_transaction_cmd_wait *E = tb_alloc_logevent (&T, LEV_COPYEXEC_AUX_TRANSACTION_CMD_CANCEL, sizeof (struct lev_copyexec_aux_transaction_cmd_wait));
  E->transaction_id = transaction_id;
  return 0;
}