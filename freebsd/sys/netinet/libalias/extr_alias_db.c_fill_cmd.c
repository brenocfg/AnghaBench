#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_6__ {int opcode; int len; int /*<<< orphan*/  arg1; } ;
typedef  TYPE_1__ ipfw_insn ;
typedef  enum ipfw_opcodes { ____Placeholder_ipfw_opcodes } ipfw_opcodes ;

/* Variables and functions */
 int F_LEN_MASK ; 
 int F_NOT ; 
 int F_OR ; 
 TYPE_1__* next_cmd (TYPE_1__*) ; 

__attribute__((used)) static ipfw_insn *
fill_cmd(ipfw_insn * cmd, enum ipfw_opcodes opcode, int size,
    int flags, u_int16_t arg)
{
	cmd->opcode = opcode;
	cmd->len = ((cmd->len | flags) & (F_NOT | F_OR)) | (size & F_LEN_MASK);
	cmd->arg1 = arg;
	return next_cmd(cmd);
}