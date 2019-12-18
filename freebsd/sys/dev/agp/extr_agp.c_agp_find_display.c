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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ PCIC_DISPLAY ; 
 scalar_t__ PCIS_DISPLAY_VGA ; 
 scalar_t__ agp_find_caps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/  devclass_get_device (int /*<<< orphan*/ ,int) ; 
 int devclass_get_maxunit (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 

__attribute__((used)) static device_t
agp_find_display(void)
{
	devclass_t pci = devclass_find("pci");
	device_t bus, dev = 0;
	device_t *kids;
	int busnum, numkids, i;

	for (busnum = 0; busnum < devclass_get_maxunit(pci); busnum++) {
		bus = devclass_get_device(pci, busnum);
		if (!bus)
			continue;
		if (device_get_children(bus, &kids, &numkids) != 0)
			continue;
		for (i = 0; i < numkids; i++) {
			dev = kids[i];
			if (pci_get_class(dev) == PCIC_DISPLAY
			    && pci_get_subclass(dev) == PCIS_DISPLAY_VGA)
				if (agp_find_caps(dev)) {
					free(kids, M_TEMP);
					return dev;
				}
					
		}
		free(kids, M_TEMP);
	}

	return 0;
}