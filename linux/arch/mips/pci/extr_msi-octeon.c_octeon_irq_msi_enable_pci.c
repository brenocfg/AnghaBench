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
struct irq_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void octeon_irq_msi_enable_pci(struct irq_data *data)
{
	/*
	 * Octeon PCI doesn't have the ability to mask/unmask MSI
	 * interrupts individually. Instead of masking/unmasking them
	 * in groups of 16, we simple assume MSI devices are well
	 * behaved. MSI interrupts are always enable and the ACK is
	 * assumed to be enough
	 */
}