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
struct pt_regs {unsigned long* uregs; } ;

/* Variables and functions */
 scalar_t__ LDST_L_BIT (unsigned long) ; 
 size_t RD_BITS (unsigned long) ; 
 size_t RM_BITS (unsigned long) ; 
 int TYPE_FAULT ; 
 int TYPE_LDST ; 
 int TYPE_SWAP ; 
 int /*<<< orphan*/  get16_unaligned_check (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  get32_unaligned_check (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  put16_unaligned_check (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  put32_unaligned_check (unsigned long,unsigned long) ; 

__attribute__((used)) static int
do_alignment_ldrhstrh(unsigned long addr, unsigned long instr,
		      struct pt_regs *regs)
{
	unsigned int rd = RD_BITS(instr);

	/* old value 0x40002120, can't judge swap instr correctly */
	if ((instr & 0x4b003fe0) == 0x40000120)
		goto swp;

	if (LDST_L_BIT(instr)) {
		unsigned long val;
		get16_unaligned_check(val, addr);

		/* signed half-word? */
		if (instr & 0x80)
			val = (signed long)((signed short)val);

		regs->uregs[rd] = val;
	} else
		put16_unaligned_check(regs->uregs[rd], addr);

	return TYPE_LDST;

swp:
	/* only handle swap word
	 * for swap byte should not active this alignment exception */
	get32_unaligned_check(regs->uregs[RD_BITS(instr)], addr);
	put32_unaligned_check(regs->uregs[RM_BITS(instr)], addr);
	return TYPE_SWAP;

fault:
	return TYPE_FAULT;
}