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
typedef  size_t u8 ;
typedef  int u32 ;
struct pt_regs {unsigned long* gpr; int ccr; } ;

/* Variables and functions */

__attribute__((used)) static int emulate_isel(struct pt_regs *regs, u32 instword)
{
	u8 rT = (instword >> 21) & 0x1f;
	u8 rA = (instword >> 16) & 0x1f;
	u8 rB = (instword >> 11) & 0x1f;
	u8 BC = (instword >> 6) & 0x1f;
	u8 bit;
	unsigned long tmp;

	tmp = (rA == 0) ? 0 : regs->gpr[rA];
	bit = (regs->ccr >> (31 - BC)) & 0x1;

	regs->gpr[rT] = bit ? tmp : regs->gpr[rB];

	return 0;
}