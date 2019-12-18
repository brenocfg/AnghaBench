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
typedef  int u32 ;
struct pt_regs {unsigned long* uregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDST_L_BIT (int) ; 
 unsigned int RD_BITS (int) ; 
 int TYPE_ERROR ; 
 int TYPE_FAULT ; 
 int TYPE_LDST ; 
 int ai_dword ; 
 int /*<<< orphan*/  get32_unaligned_check (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  get32t_unaligned_check (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  put32_unaligned_check (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  put32t_unaligned_check (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  uaccess_restore (unsigned int) ; 
 unsigned int uaccess_save_and_enable () ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static int
do_alignment_ldrdstrd(unsigned long addr, u32 instr, struct pt_regs *regs)
{
	unsigned int rd = RD_BITS(instr);
	unsigned int rd2;
	int load;

	if ((instr & 0xfe000000) == 0xe8000000) {
		/* ARMv7 Thumb-2 32-bit LDRD/STRD */
		rd2 = (instr >> 8) & 0xf;
		load = !!(LDST_L_BIT(instr));
	} else if (((rd & 1) == 1) || (rd == 14))
		goto bad;
	else {
		load = ((instr & 0xf0) == 0xd0);
		rd2 = rd + 1;
	}

	ai_dword += 1;

	if (user_mode(regs))
		goto user;

	if (load) {
		unsigned long val;
		get32_unaligned_check(val, addr);
		regs->uregs[rd] = val;
		get32_unaligned_check(val, addr + 4);
		regs->uregs[rd2] = val;
	} else {
		put32_unaligned_check(regs->uregs[rd], addr);
		put32_unaligned_check(regs->uregs[rd2], addr + 4);
	}

	return TYPE_LDST;

 user:
	if (load) {
		unsigned long val, val2;
		unsigned int __ua_flags = uaccess_save_and_enable();

		get32t_unaligned_check(val, addr);
		get32t_unaligned_check(val2, addr + 4);

		uaccess_restore(__ua_flags);

		regs->uregs[rd] = val;
		regs->uregs[rd2] = val2;
	} else {
		unsigned int __ua_flags = uaccess_save_and_enable();
		put32t_unaligned_check(regs->uregs[rd], addr);
		put32t_unaligned_check(regs->uregs[rd2], addr + 4);
		uaccess_restore(__ua_flags);
	}

	return TYPE_LDST;
 bad:
	return TYPE_ERROR;
 fault:
	return TYPE_FAULT;
}