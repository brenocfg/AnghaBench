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
 int PIC_PCIE_LINK_MSI_IRQ (int) ; 
 int PIC_PCIE_MSIX_IRQ (int) ; 
 scalar_t__ cpu_is_xlp9xx () ; 
 int xlp9xx_irq_to_irt (int) ; 
 int xlp_irq_to_irt (int) ; 

int nlm_irq_to_irt(int irq)
{
	/* return -2 for irqs without 1-1 mapping */
	if (irq >= PIC_PCIE_LINK_MSI_IRQ(0) && irq <= PIC_PCIE_LINK_MSI_IRQ(3))
		return -2;
	if (irq >= PIC_PCIE_MSIX_IRQ(0) && irq <= PIC_PCIE_MSIX_IRQ(3))
		return -2;

	if (cpu_is_xlp9xx())
		return xlp9xx_irq_to_irt(irq);
	else
		return xlp_irq_to_irt(irq);
}