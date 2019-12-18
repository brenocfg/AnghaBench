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
struct pt_regs {int tstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_32BIT ; 
 int TSTATE_PRIV ; 
 unsigned long fetch_reg (unsigned int,struct pt_regs*) ; 
 int /*<<< orphan*/  maybe_flush_windows (unsigned int,unsigned int,unsigned int,int) ; 
 unsigned long sign_extend_imm13 (unsigned int) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 

unsigned long compute_effective_address(struct pt_regs *regs,
					unsigned int insn, unsigned int rd)
{
	int from_kernel = (regs->tstate & TSTATE_PRIV) != 0;
	unsigned int rs1 = (insn >> 14) & 0x1f;
	unsigned int rs2 = insn & 0x1f;
	unsigned long addr;

	if (insn & 0x2000) {
		maybe_flush_windows(rs1, 0, rd, from_kernel);
		addr = (fetch_reg(rs1, regs) + sign_extend_imm13(insn));
	} else {
		maybe_flush_windows(rs1, rs2, rd, from_kernel);
		addr = (fetch_reg(rs1, regs) + fetch_reg(rs2, regs));
	}

	if (!from_kernel && test_thread_flag(TIF_32BIT))
		addr &= 0xffffffff;

	return addr;
}