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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int GAPSPCI_IRQ ; 

int pcibios_map_platform_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	/*
	 * The interrupt routing semantics here are quite trivial.
	 *
	 * We basically only support one interrupt, so we only bother
	 * updating a device's interrupt line with this single shared
	 * interrupt. Keeps routing quite simple, doesn't it?
	 */
	return GAPSPCI_IRQ;
}