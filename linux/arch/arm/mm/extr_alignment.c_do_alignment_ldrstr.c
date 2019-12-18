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
struct pt_regs {unsigned int* uregs; } ;

/* Variables and functions */
 scalar_t__ LDST_L_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDST_P_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ LDST_W_BIT (int /*<<< orphan*/ ) ; 
 unsigned int RD_BITS (int /*<<< orphan*/ ) ; 
 int TYPE_FAULT ; 
 int TYPE_LDST ; 
 int ai_word ; 
 int /*<<< orphan*/  get32_unaligned_check (unsigned int,unsigned long) ; 
 int /*<<< orphan*/  get32t_unaligned_check (unsigned int,unsigned long) ; 
 int /*<<< orphan*/  put32_unaligned_check (unsigned int,unsigned long) ; 
 int /*<<< orphan*/  put32t_unaligned_check (unsigned int,unsigned long) ; 
 int /*<<< orphan*/  uaccess_restore (unsigned int) ; 
 unsigned int uaccess_save_and_enable () ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static int
do_alignment_ldrstr(unsigned long addr, u32 instr, struct pt_regs *regs)
{
	unsigned int rd = RD_BITS(instr);

	ai_word += 1;

	if ((!LDST_P_BIT(instr) && LDST_W_BIT(instr)) || user_mode(regs))
		goto trans;

	if (LDST_L_BIT(instr)) {
		unsigned int val;
		get32_unaligned_check(val, addr);
		regs->uregs[rd] = val;
	} else
		put32_unaligned_check(regs->uregs[rd], addr);
	return TYPE_LDST;

 trans:
	if (LDST_L_BIT(instr)) {
		unsigned int val;
		unsigned int __ua_flags = uaccess_save_and_enable();
		get32t_unaligned_check(val, addr);
		uaccess_restore(__ua_flags);
		regs->uregs[rd] = val;
	} else {
		unsigned int __ua_flags = uaccess_save_and_enable();
		put32t_unaligned_check(regs->uregs[rd], addr);
		uaccess_restore(__ua_flags);
	}
	return TYPE_LDST;

 fault:
	return TYPE_FAULT;
}