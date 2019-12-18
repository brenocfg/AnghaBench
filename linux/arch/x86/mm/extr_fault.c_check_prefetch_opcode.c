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

/* Variables and functions */
 int /*<<< orphan*/  probe_kernel_address (unsigned char*,unsigned char) ; 
 int /*<<< orphan*/  user_64bit_mode (struct pt_regs*) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

__attribute__((used)) static inline int
check_prefetch_opcode(struct pt_regs *regs, unsigned char *instr,
		      unsigned char opcode, int *prefetch)
{
	unsigned char instr_hi = opcode & 0xf0;
	unsigned char instr_lo = opcode & 0x0f;

	switch (instr_hi) {
	case 0x20:
	case 0x30:
		/*
		 * Values 0x26,0x2E,0x36,0x3E are valid x86 prefixes.
		 * In X86_64 long mode, the CPU will signal invalid
		 * opcode if some of these prefixes are present so
		 * X86_64 will never get here anyway
		 */
		return ((instr_lo & 7) == 0x6);
#ifdef CONFIG_X86_64
	case 0x40:
		/*
		 * In AMD64 long mode 0x40..0x4F are valid REX prefixes
		 * Need to figure out under what instruction mode the
		 * instruction was issued. Could check the LDT for lm,
		 * but for now it's good enough to assume that long
		 * mode only uses well known segments or kernel.
		 */
		return (!user_mode(regs) || user_64bit_mode(regs));
#endif
	case 0x60:
		/* 0x64 thru 0x67 are valid prefixes in all modes. */
		return (instr_lo & 0xC) == 0x4;
	case 0xF0:
		/* 0xF0, 0xF2, 0xF3 are valid prefixes in all modes. */
		return !instr_lo || (instr_lo>>1) == 1;
	case 0x00:
		/* Prefetch instruction is 0x0F0D or 0x0F18 */
		if (probe_kernel_address(instr, opcode))
			return 0;

		*prefetch = (instr_lo == 0xF) &&
			(opcode == 0x0D || opcode == 0x18);
		return 0;
	default:
		return 0;
	}
}