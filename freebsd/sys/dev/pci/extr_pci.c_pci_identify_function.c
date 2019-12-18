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
 int /*<<< orphan*/  pci_add_child (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 struct pci_devinfo* pci_read_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static struct pci_devinfo *
pci_identify_function(device_t pcib, device_t dev, int domain, int busno,
    int slot, int func)
{
	struct pci_devinfo *dinfo;

	dinfo = pci_read_device(pcib, dev, domain, busno, slot, func);
	if (dinfo != NULL)
		pci_add_child(dev, dinfo);

	return (dinfo);
}