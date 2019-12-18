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
struct pcicfg_msix {scalar_t__ msix_location; int msix_table_bar; } ;
struct TYPE_2__ {struct pcicfg_msix msix; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_do_msix ; 

int
pci_msix_table_bar_method(device_t dev, device_t child)
{
	struct pci_devinfo *dinfo = device_get_ivars(child);
	struct pcicfg_msix *msix = &dinfo->cfg.msix;

	if (pci_do_msix && msix->msix_location != 0)
		return (msix->msix_table_bar);
	return (-1);
}