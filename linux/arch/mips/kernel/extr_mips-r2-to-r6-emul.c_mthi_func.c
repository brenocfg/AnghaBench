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
struct pt_regs {int /*<<< orphan*/ * regs; int /*<<< orphan*/  hi; } ;

/* Variables and functions */
 size_t MIPSInst_RS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIPS_R2_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hilo ; 

__attribute__((used)) static int mthi_func(struct pt_regs *regs, u32 ir)
{
	regs->hi = regs->regs[MIPSInst_RS(ir)];

	MIPS_R2_STATS(hilo);

	return 0;
}