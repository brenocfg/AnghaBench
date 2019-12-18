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
struct pt_regs {unsigned int ARM_pc; unsigned long* uregs; } ;

/* Variables and functions */
 scalar_t__ LDM_S_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ LDST_L_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ LDST_P_EQ_U (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDST_U_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ LDST_W_BIT (int /*<<< orphan*/ ) ; 
 int REGMASK_BITS (int /*<<< orphan*/ ) ; 
 unsigned int RN_BITS (int /*<<< orphan*/ ) ; 
 int TYPE_DONE ; 
 int TYPE_ERROR ; 
 int TYPE_FAULT ; 
 int ai_multi ; 
 int /*<<< orphan*/  get32_unaligned_check (unsigned int,unsigned long) ; 
 int /*<<< orphan*/  get32t_unaligned_check (unsigned int,unsigned long) ; 
 int hweight16 (int) ; 
 int /*<<< orphan*/  instruction_pointer (struct pt_regs*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  put32_unaligned_check (unsigned int,unsigned long) ; 
 int /*<<< orphan*/  put32t_unaligned_check (unsigned int,unsigned long) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  uaccess_restore (unsigned int) ; 
 unsigned int uaccess_save_and_enable () ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static int
do_alignment_ldmstm(unsigned long addr, u32 instr, struct pt_regs *regs)
{
	unsigned int rd, rn, correction, nr_regs, regbits;
	unsigned long eaddr, newaddr;

	if (LDM_S_BIT(instr))
		goto bad;

	correction = 4; /* processor implementation defined */
	regs->ARM_pc += correction;

	ai_multi += 1;

	/* count the number of registers in the mask to be transferred */
	nr_regs = hweight16(REGMASK_BITS(instr)) * 4;

	rn = RN_BITS(instr);
	newaddr = eaddr = regs->uregs[rn];

	if (!LDST_U_BIT(instr))
		nr_regs = -nr_regs;
	newaddr += nr_regs;
	if (!LDST_U_BIT(instr))
		eaddr = newaddr;

	if (LDST_P_EQ_U(instr))	/* U = P */
		eaddr += 4;

	/*
	 * For alignment faults on the ARM922T/ARM920T the MMU  makes
	 * the FSR (and hence addr) equal to the updated base address
	 * of the multiple access rather than the restored value.
	 * Switch this message off if we've got a ARM92[02], otherwise
	 * [ls]dm alignment faults are noisy!
	 */
#if !(defined CONFIG_CPU_ARM922T)  && !(defined CONFIG_CPU_ARM920T)
	/*
	 * This is a "hint" - we already have eaddr worked out by the
	 * processor for us.
	 */
	if (addr != eaddr) {
		pr_err("LDMSTM: PC = %08lx, instr = %08x, "
			"addr = %08lx, eaddr = %08lx\n",
			 instruction_pointer(regs), instr, addr, eaddr);
		show_regs(regs);
	}
#endif

	if (user_mode(regs)) {
		unsigned int __ua_flags = uaccess_save_and_enable();
		for (regbits = REGMASK_BITS(instr), rd = 0; regbits;
		     regbits >>= 1, rd += 1)
			if (regbits & 1) {
				if (LDST_L_BIT(instr)) {
					unsigned int val;
					get32t_unaligned_check(val, eaddr);
					regs->uregs[rd] = val;
				} else
					put32t_unaligned_check(regs->uregs[rd], eaddr);
				eaddr += 4;
			}
		uaccess_restore(__ua_flags);
	} else {
		for (regbits = REGMASK_BITS(instr), rd = 0; regbits;
		     regbits >>= 1, rd += 1)
			if (regbits & 1) {
				if (LDST_L_BIT(instr)) {
					unsigned int val;
					get32_unaligned_check(val, eaddr);
					regs->uregs[rd] = val;
				} else
					put32_unaligned_check(regs->uregs[rd], eaddr);
				eaddr += 4;
			}
	}

	if (LDST_W_BIT(instr))
		regs->uregs[rn] = newaddr;
	if (!LDST_L_BIT(instr) || !(REGMASK_BITS(instr) & (1 << 15)))
		regs->ARM_pc -= correction;
	return TYPE_DONE;

fault:
	regs->ARM_pc -= correction;
	return TYPE_FAULT;

bad:
	pr_err("Alignment trap: not handling ldm with s-bit set\n");
	return TYPE_ERROR;
}