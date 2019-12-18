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
struct pci_devinfo {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_cfg_restore (int /*<<< orphan*/ ,struct pci_devinfo*) ; 

void
pci_restore_state(device_t dev)
{
	struct pci_devinfo *dinfo;

	dinfo = device_get_ivars(dev);
	pci_cfg_restore(dev, dinfo);
}