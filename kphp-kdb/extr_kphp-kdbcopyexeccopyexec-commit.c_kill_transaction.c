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
struct lev_copyexec_aux_transaction_cmd_kill {int signal; int transaction_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_COPYEXEC_AUX_TRANSACTION_CMD_KILL ; 
 int SIGINT ; 
 int SIGKILL ; 
 int SIGTERM ; 
 int /*<<< orphan*/  T ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 struct lev_copyexec_aux_transaction_cmd_kill* tb_alloc_logevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int transactions ; 

__attribute__((used)) static int kill_transaction (int signal, int transaction_id) {
  if (transaction_id < 1) {
    kprintf ("kill_transaction: X < 1\n");
    return -1;
  }
  if (transaction_id >= transactions + 1) {
    kprintf ("kill_transaction: X >= current transaction id (X = %d, transaction_id = %d)\n", transaction_id, transactions + 1);
    return -2;
  }
  if (signal != SIGINT && signal != SIGTERM && signal != SIGKILL) {
    kprintf ("kill_transaction: Unknown signal: %d\n", signal);
    return -3;
  }
  struct lev_copyexec_aux_transaction_cmd_kill *E = tb_alloc_logevent (&T, LEV_COPYEXEC_AUX_TRANSACTION_CMD_KILL, sizeof (struct lev_copyexec_aux_transaction_cmd_kill));
  E->signal = signal;
  E->transaction_id = transaction_id;
  return 0;
}