#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* pcibios_fixup_sriov ) (struct pci_dev*) ;} ;
struct TYPE_3__ {scalar_t__ is_added; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcibios_setup_device (struct pci_dev*) ; 
 TYPE_2__ ppc_md ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*) ; 

int pcibios_add_device(struct pci_dev *dev)
{
	/*
	 * We can only call pcibios_setup_device() after bus setup is complete,
	 * since some of the platform specific DMA setup code depends on it.
	 */
	if (dev->bus->is_added)
		pcibios_setup_device(dev);

#ifdef CONFIG_PCI_IOV
	if (ppc_md.pcibios_fixup_sriov)
		ppc_md.pcibios_fixup_sriov(dev);
#endif /* CONFIG_PCI_IOV */

	return 0;
}