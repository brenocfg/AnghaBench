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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  register_t ;
typedef  scalar_t__ db_addr_t ;

/* Variables and functions */
 int arm_predict_branch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_branch_taken_fetch_reg ; 
 int /*<<< orphan*/  db_branch_taken_read_int ; 
 int /*<<< orphan*/  kdb_reenter () ; 

u_int
branch_taken(u_int insn, db_addr_t pc)
{
	register_t new_pc;
	int ret;

	ret = arm_predict_branch(NULL, insn, (register_t)pc, &new_pc,
	    db_branch_taken_fetch_reg, db_branch_taken_read_int);

	if (ret != 0)
		kdb_reenter();

	return (new_pc);
}