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
struct pcicfg_msi {scalar_t__ msi_location; int msi_msgnum; } ;
struct TYPE_2__ {struct pcicfg_msi msi; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_do_msi ; 

int
pci_msi_count_method(device_t dev, device_t child)
{
	struct pci_devinfo *dinfo = device_get_ivars(child);
	struct pcicfg_msi *msi = &dinfo->cfg.msi;

	if (pci_do_msi && msi->msi_location != 0)
		return (msi->msi_msgnum);
	return (0);
}