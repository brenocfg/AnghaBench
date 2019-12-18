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
typedef  int db_expr_t ;

/* Variables and functions */
 int /*<<< orphan*/  STEP_ONCE ; 
 int db_cmd_loop_done ; 
 scalar_t__ db_inst_count ; 
 scalar_t__ db_load_count ; 
 int db_loop_count ; 
 int /*<<< orphan*/  db_run_mode ; 
 int db_sstep_multiple ; 
 int db_sstep_print ; 
 scalar_t__ db_store_count ; 

void
db_single_step_cmd(db_expr_t addr, bool have_addr, db_expr_t count, char *modif)
{
	bool		print = false;

	if (count == -1)
	    count = 1;

	if (modif[0] == 'p')
	    print = true;

	db_run_mode = STEP_ONCE;
	db_loop_count = count;
	db_sstep_multiple = (count != 1);
	db_sstep_print = print;
	db_inst_count = 0;
	db_load_count = 0;
	db_store_count = 0;

	db_cmd_loop_done = 1;
}