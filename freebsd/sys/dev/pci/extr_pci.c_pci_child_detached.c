#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource_list {int dummy; } ;
struct TYPE_5__ {scalar_t__ msix_alloc; } ;
struct TYPE_4__ {scalar_t__ msi_alloc; } ;
struct TYPE_6__ {TYPE_2__ msix; TYPE_1__ msi; } ;
struct pci_devinfo {TYPE_3__ cfg; struct resource_list resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_RES_BUS ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_cfg_save (int /*<<< orphan*/ ,struct pci_devinfo*,int) ; 
 int /*<<< orphan*/  pci_printf (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_list_release_active (struct resource_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pci_child_detached(device_t dev, device_t child)
{
	struct pci_devinfo *dinfo;
	struct resource_list *rl;

	dinfo = device_get_ivars(child);
	rl = &dinfo->resources;

	/*
	 * Have to deallocate IRQs before releasing any MSI messages and
	 * have to release MSI messages before deallocating any memory
	 * BARs.
	 */
	if (resource_list_release_active(rl, dev, child, SYS_RES_IRQ) != 0)
		pci_printf(&dinfo->cfg, "Device leaked IRQ resources\n");
	if (dinfo->cfg.msi.msi_alloc != 0 || dinfo->cfg.msix.msix_alloc != 0) {
		pci_printf(&dinfo->cfg, "Device leaked MSI vectors\n");
		(void)pci_release_msi(child);
	}
	if (resource_list_release_active(rl, dev, child, SYS_RES_MEMORY) != 0)
		pci_printf(&dinfo->cfg, "Device leaked memory resources\n");
	if (resource_list_release_active(rl, dev, child, SYS_RES_IOPORT) != 0)
		pci_printf(&dinfo->cfg, "Device leaked I/O resources\n");
#ifdef PCI_RES_BUS
	if (resource_list_release_active(rl, dev, child, PCI_RES_BUS) != 0)
		pci_printf(&dinfo->cfg, "Device leaked PCI bus numbers\n");
#endif

	pci_cfg_save(child, dinfo, 1);
}