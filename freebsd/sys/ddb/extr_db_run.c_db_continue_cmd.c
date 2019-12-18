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
typedef  int /*<<< orphan*/  db_expr_t ;

/* Variables and functions */
 int /*<<< orphan*/  STEP_CONTINUE ; 
 int /*<<< orphan*/  STEP_COUNT ; 
 int db_cmd_loop_done ; 
 scalar_t__ db_inst_count ; 
 scalar_t__ db_load_count ; 
 int /*<<< orphan*/  db_run_mode ; 
 scalar_t__ db_store_count ; 

void
db_continue_cmd(db_expr_t addr, bool have_addr, db_expr_t count, char *modif)
{
	if (modif[0] == 'c')
	    db_run_mode = STEP_COUNT;
	else
	    db_run_mode = STEP_CONTINUE;
	db_inst_count = 0;
	db_load_count = 0;
	db_store_count = 0;

	db_cmd_loop_done = 1;
}