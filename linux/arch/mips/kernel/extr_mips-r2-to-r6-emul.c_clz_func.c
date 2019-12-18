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
struct pt_regs {int /*<<< orphan*/ * regs; } ;

/* Variables and functions */
 size_t MIPSInst_RD (int /*<<< orphan*/ ) ; 
 size_t MIPSInst_RS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIPS_R2_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bops ; 

__attribute__((used)) static int clz_func(struct pt_regs *regs, u32 ir)
{
	u32 res;
	u32 rs;

	if (!MIPSInst_RD(ir))
		return 0;

	rs = regs->regs[MIPSInst_RS(ir)];
	__asm__ __volatile__("clz %0, %1" : "=r"(res) : "r"(rs));
	regs->regs[MIPSInst_RD(ir)] = res;

	MIPS_R2_STATS(bops);

	return 0;
}