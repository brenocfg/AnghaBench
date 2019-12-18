#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {TYPE_1__ addr; } ;
typedef  TYPE_2__ ipfw_insn_ip ;
typedef  int /*<<< orphan*/  ipfw_insn ;
typedef  enum ipfw_opcodes { ____Placeholder_ipfw_opcodes } ipfw_opcodes ;

/* Variables and functions */
 int /*<<< orphan*/  F_INSN_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fill_cmd (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipfw_insn_u32 ; 

__attribute__((used)) static ipfw_insn *
fill_ip(ipfw_insn * cmd1, enum ipfw_opcodes opcode, u_int32_t addr)
{
	ipfw_insn_ip *cmd = (ipfw_insn_ip *) cmd1;

	cmd->addr.s_addr = addr;
	return fill_cmd(cmd1, opcode, F_INSN_SIZE(ipfw_insn_u32), 0, 0);
}