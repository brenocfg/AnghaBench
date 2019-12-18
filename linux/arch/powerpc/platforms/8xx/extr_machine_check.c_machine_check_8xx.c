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
struct pt_regs {unsigned long msr; int /*<<< orphan*/  dar; int /*<<< orphan*/  nip; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  bad_page_fault (struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

int machine_check_8xx(struct pt_regs *regs)
{
	unsigned long reason = regs->msr;

	pr_err("Machine check in kernel mode.\n");
	pr_err("Caused by (from SRR1=%lx): ", reason);
	if (reason & 0x40000000)
		pr_cont("Fetch error at address %lx\n", regs->nip);
	else
		pr_cont("Data access error at address %lx\n", regs->dar);

#ifdef CONFIG_PCI
	/* the qspan pci read routines can cause machine checks -- Cort
	 *
	 * yuck !!! that totally needs to go away ! There are better ways
	 * to deal with that than having a wart in the mcheck handler.
	 * -- BenH
	 */
	bad_page_fault(regs, regs->dar, SIGBUS);
	return 1;
#else
	return 0;
#endif
}