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
 unsigned char NMI_REASON_CLEAR_MASK ; 
 unsigned char NMI_REASON_CLEAR_SERR ; 
 int /*<<< orphan*/  NMI_REASON_PORT ; 
 int /*<<< orphan*/  NMI_SERR ; 
 scalar_t__ nmi_handle (int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  nmi_panic (struct pt_regs*,char*) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 scalar_t__ panic_on_unrecovered_nmi ; 
 int /*<<< orphan*/  pr_emerg (char*,...) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void
pci_serr_error(unsigned char reason, struct pt_regs *regs)
{
	/* check to see if anyone registered against these types of errors */
	if (nmi_handle(NMI_SERR, regs))
		return;

	pr_emerg("NMI: PCI system error (SERR) for reason %02x on CPU %d.\n",
		 reason, smp_processor_id());

	if (panic_on_unrecovered_nmi)
		nmi_panic(regs, "NMI: Not continuing");

	pr_emerg("Dazed and confused, but trying to continue\n");

	/* Clear and disable the PCI SERR error line. */
	reason = (reason & NMI_REASON_CLEAR_MASK) | NMI_REASON_CLEAR_SERR;
	outb(reason, NMI_REASON_PORT);
}