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
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mem_to_opcode_arm (int /*<<< orphan*/ ) ; 
 int get_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int probe_kernel_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static int alignment_get_arm(struct pt_regs *regs, u32 *ip, u32 *inst)
{
	u32 instr = 0;
	int fault;

	if (user_mode(regs))
		fault = get_user(instr, ip);
	else
		fault = probe_kernel_address(ip, instr);

	*inst = __mem_to_opcode_arm(instr);

	return fault;
}