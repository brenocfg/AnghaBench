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
struct pt_regs {int dummy; } ;
struct instruction_op {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int GETTYPE (int /*<<< orphan*/ ) ; 
 int LARX ; 
 int STCX ; 
 int analyse_instr (struct instruction_op*,struct pt_regs*,unsigned int) ; 

__attribute__((used)) static bool is_larx_stcx_instr(struct pt_regs *regs, unsigned int instr)
{
	int ret, type;
	struct instruction_op op;

	ret = analyse_instr(&op, regs, instr);
	type = GETTYPE(op.type);
	return (!ret && (type == LARX || type == STCX));
}