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
typedef  int /*<<< orphan*/  uint32_t ;
struct pt_regs {unsigned int cp0_cause; unsigned int acx; unsigned int hi; unsigned int lo; int cp0_status; unsigned int cp0_badvaddr; scalar_t__* regs; scalar_t__ cp0_epc; } ;

/* Variables and functions */
 unsigned int CAUSEB_EXCCODE ; 
 unsigned int CAUSEF_EXCCODE ; 
 int /*<<< orphan*/  KERN_DEFAULT ; 
#define  KSU_KERNEL 130 
#define  KSU_SUPERVISOR 129 
#define  KSU_USER 128 
 int MIPS_ISA_REV ; 
 int ST0_ERL ; 
 int ST0_EXL ; 
 int ST0_IE ; 
 int ST0_IEC ; 
 int ST0_IEO ; 
 int ST0_IEP ; 
 int ST0_KSU ; 
 int ST0_KUC ; 
 int ST0_KUO ; 
 int ST0_KUP ; 
 int ST0_KX ; 
 int ST0_SX ; 
 int ST0_UX ; 
 scalar_t__ cpu_has_3kex ; 
 scalar_t__ cpu_has_4kex ; 
 unsigned int cpu_name_string () ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  printk (char*,int const,...) ; 
 int const read_c0_prid () ; 
 int /*<<< orphan*/  show_regs_print_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __show_regs(const struct pt_regs *regs)
{
	const int field = 2 * sizeof(unsigned long);
	unsigned int cause = regs->cp0_cause;
	unsigned int exccode;
	int i;

	show_regs_print_info(KERN_DEFAULT);

	/*
	 * Saved main processor registers
	 */
	for (i = 0; i < 32; ) {
		if ((i % 4) == 0)
			printk("$%2d   :", i);
		if (i == 0)
			pr_cont(" %0*lx", field, 0UL);
		else if (i == 26 || i == 27)
			pr_cont(" %*s", field, "");
		else
			pr_cont(" %0*lx", field, regs->regs[i]);

		i++;
		if ((i % 4) == 0)
			pr_cont("\n");
	}

#ifdef CONFIG_CPU_HAS_SMARTMIPS
	printk("Acx    : %0*lx\n", field, regs->acx);
#endif
	if (MIPS_ISA_REV < 6) {
		printk("Hi    : %0*lx\n", field, regs->hi);
		printk("Lo    : %0*lx\n", field, regs->lo);
	}

	/*
	 * Saved cp0 registers
	 */
	printk("epc   : %0*lx %pS\n", field, regs->cp0_epc,
	       (void *) regs->cp0_epc);
	printk("ra    : %0*lx %pS\n", field, regs->regs[31],
	       (void *) regs->regs[31]);

	printk("Status: %08x	", (uint32_t) regs->cp0_status);

	if (cpu_has_3kex) {
		if (regs->cp0_status & ST0_KUO)
			pr_cont("KUo ");
		if (regs->cp0_status & ST0_IEO)
			pr_cont("IEo ");
		if (regs->cp0_status & ST0_KUP)
			pr_cont("KUp ");
		if (regs->cp0_status & ST0_IEP)
			pr_cont("IEp ");
		if (regs->cp0_status & ST0_KUC)
			pr_cont("KUc ");
		if (regs->cp0_status & ST0_IEC)
			pr_cont("IEc ");
	} else if (cpu_has_4kex) {
		if (regs->cp0_status & ST0_KX)
			pr_cont("KX ");
		if (regs->cp0_status & ST0_SX)
			pr_cont("SX ");
		if (regs->cp0_status & ST0_UX)
			pr_cont("UX ");
		switch (regs->cp0_status & ST0_KSU) {
		case KSU_USER:
			pr_cont("USER ");
			break;
		case KSU_SUPERVISOR:
			pr_cont("SUPERVISOR ");
			break;
		case KSU_KERNEL:
			pr_cont("KERNEL ");
			break;
		default:
			pr_cont("BAD_MODE ");
			break;
		}
		if (regs->cp0_status & ST0_ERL)
			pr_cont("ERL ");
		if (regs->cp0_status & ST0_EXL)
			pr_cont("EXL ");
		if (regs->cp0_status & ST0_IE)
			pr_cont("IE ");
	}
	pr_cont("\n");

	exccode = (cause & CAUSEF_EXCCODE) >> CAUSEB_EXCCODE;
	printk("Cause : %08x (ExcCode %02x)\n", cause, exccode);

	if (1 <= exccode && exccode <= 5)
		printk("BadVA : %0*lx\n", field, regs->cp0_badvaddr);

	printk("PrId  : %08x (%s)\n", read_c0_prid(),
	       cpu_name_string());
}