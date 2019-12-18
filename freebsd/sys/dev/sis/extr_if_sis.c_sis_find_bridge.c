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
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/ * devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ SIS_VENDORID ; 
 int /*<<< orphan*/ * devclass_find (char*) ; 
 int /*<<< orphan*/  devclass_get_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,int*) ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,int*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int pci_get_device (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static device_t
sis_find_bridge(device_t dev)
{
	devclass_t		pci_devclass;
	device_t		*pci_devices;
	int			pci_count = 0;
	device_t		*pci_children;
	int			pci_childcount = 0;
	device_t		*busp, *childp;
	device_t		child = NULL;
	int			i, j;

	if ((pci_devclass = devclass_find("pci")) == NULL)
		return (NULL);

	devclass_get_devices(pci_devclass, &pci_devices, &pci_count);

	for (i = 0, busp = pci_devices; i < pci_count; i++, busp++) {
		if (device_get_children(*busp, &pci_children, &pci_childcount))
			continue;
		for (j = 0, childp = pci_children;
		    j < pci_childcount; j++, childp++) {
			if (pci_get_vendor(*childp) == SIS_VENDORID &&
			    pci_get_device(*childp) == 0x0008) {
				child = *childp;
				free(pci_children, M_TEMP);
				goto done;
			}
		}
		free(pci_children, M_TEMP);
	}

done:
	free(pci_devices, M_TEMP);
	return (child);
}