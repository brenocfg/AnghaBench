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

/* Variables and functions */
 int READ_SPECIALREG (int /*<<< orphan*/ ) ; 
 int SCTLR_SPAN ; 
 int /*<<< orphan*/  WRITE_SPECIALREG (int /*<<< orphan*/ ,int) ; 
 scalar_t__ has_pan ; 
 int /*<<< orphan*/  sctlr_el1 ; 

void
pan_enable(void)
{

	/*
	 * The LLVM integrated assembler doesn't understand the PAN
	 * PSTATE field. Because of this we need to manually create
	 * the instruction in an asm block. This is equivalent to:
	 * msr pan, #1
	 *
	 * This sets the PAN bit, stopping the kernel from accessing
	 * memory when userspace can also access it unless the kernel
	 * uses the userspace load/store instructions.
	 */
	if (has_pan) {
		WRITE_SPECIALREG(sctlr_el1,
		    READ_SPECIALREG(sctlr_el1) & ~SCTLR_SPAN);
		__asm __volatile(".inst 0xd500409f | (0x1 << 8)");
	}
}