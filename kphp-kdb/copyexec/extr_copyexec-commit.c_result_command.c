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
struct lev_copyexec_aux_transaction_cmd_result {int result; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_COPYEXEC_AUX_TRANSACTION_CMD_RESULT ; 
 int /*<<< orphan*/  T ; 
 struct lev_copyexec_aux_transaction_cmd_result* tb_alloc_logevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int result_command (int x) {
  struct lev_copyexec_aux_transaction_cmd_result *E = tb_alloc_logevent (&T, LEV_COPYEXEC_AUX_TRANSACTION_CMD_RESULT, sizeof (struct lev_copyexec_aux_transaction_cmd_result));
  E->result = x;
  return 0;
}