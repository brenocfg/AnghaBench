#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  misc_mask; int /*<<< orphan*/  misc_status; int /*<<< orphan*/  pci_mask; int /*<<< orphan*/  pci_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  MISC_IGNORE ; 
 int /*<<< orphan*/  PCI_IGNORE ; 
 unsigned int cpld_pic_get_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* cpld_regs ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 

__attribute__((used)) static void cpld_pic_cascade(struct irq_desc *desc)
{
	unsigned int irq;

	irq = cpld_pic_get_irq(0, PCI_IGNORE, &cpld_regs->pci_status,
		&cpld_regs->pci_mask);
	if (irq) {
		generic_handle_irq(irq);
		return;
	}

	irq = cpld_pic_get_irq(8, MISC_IGNORE, &cpld_regs->misc_status,
		&cpld_regs->misc_mask);
	if (irq) {
		generic_handle_irq(irq);
		return;
	}
}