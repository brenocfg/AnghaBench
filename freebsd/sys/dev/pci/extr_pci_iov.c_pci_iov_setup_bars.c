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
struct pcicfg_iov {scalar_t__ iov_pos; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct pcicfg_iov* iov; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  scalar_t__ pci_addr_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIR_MAX_BAR_0 ; 
 scalar_t__ PCIR_SRIOV_BAR (int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_add_resources_ea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_ea_is_enabled (int /*<<< orphan*/ ,scalar_t__) ; 
 int pci_iov_alloc_bar (struct pci_devinfo*,int,int /*<<< orphan*/ ) ; 
 int pci_iov_alloc_bar_ea (struct pci_devinfo*,int) ; 
 int /*<<< orphan*/  pci_mapsize (scalar_t__) ; 
 int /*<<< orphan*/  pci_read_bar (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*,int*) ; 

__attribute__((used)) static int
pci_iov_setup_bars(struct pci_devinfo *dinfo)
{
	device_t dev;
	struct pcicfg_iov *iov;
	pci_addr_t bar_value, testval;
	int i, last_64, error;

	iov = dinfo->cfg.iov;
	dev = dinfo->cfg.dev;
	last_64 = 0;

	pci_add_resources_ea(device_get_parent(dev), dev, 1);

	for (i = 0; i <= PCIR_MAX_BAR_0; i++) {
		/* First, try to use BARs allocated with EA */
		error = pci_iov_alloc_bar_ea(dinfo, i);
		if (error == 0)
			continue;

		/* Allocate legacy-BAR only if EA is not enabled */
		if (pci_ea_is_enabled(dev, iov->iov_pos + PCIR_SRIOV_BAR(i)))
			continue;

		/*
		 * If a PCI BAR is a 64-bit wide BAR, then it spans two
		 * consecutive registers.  Therefore if the last BAR that
		 * we looked at was a 64-bit BAR, we need to skip this
		 * register as it's the second half of the last BAR.
		 */
		if (!last_64) {
			pci_read_bar(dev,
			    iov->iov_pos + PCIR_SRIOV_BAR(i),
			    &bar_value, &testval, &last_64);

			if (testval != 0) {
				error = pci_iov_alloc_bar(dinfo, i,
				   pci_mapsize(testval));
				if (error != 0)
					return (error);
			}
		} else
			last_64 = 0;
	}

	return (0);
}