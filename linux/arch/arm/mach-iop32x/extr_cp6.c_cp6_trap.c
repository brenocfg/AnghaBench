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

__attribute__((used)) static int cp6_trap(struct pt_regs *regs, unsigned int instr)
{
	u32 temp;

        /* enable cp6 access */
        asm volatile (
		"mrc	p15, 0, %0, c15, c1, 0\n\t"
		"orr	%0, %0, #(1 << 6)\n\t"
		"mcr	p15, 0, %0, c15, c1, 0\n\t"
		: "=r"(temp));

	return 0;
}