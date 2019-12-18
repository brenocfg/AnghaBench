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
typedef  int u_int16_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/ * devclass_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  X86_BUS_SPACE_IO ; 
 int bus_space_read_2 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bus_space_write_2 (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * devclass_find (char*) ; 
 int /*<<< orphan*/  devclass_get_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
clkrun_hack(int run)
{
#ifdef __i386__
	devclass_t		pci_devclass;
	device_t		*pci_devices, *pci_children, *busp, *childp;
	int			pci_count = 0, pci_childcount = 0;
	int			i, j, port;
	u_int16_t		control;
	bus_space_tag_t		btag;

	if ((pci_devclass = devclass_find("pci")) == NULL) {
		return ENXIO;
	}

	devclass_get_devices(pci_devclass, &pci_devices, &pci_count);

	for (i = 0, busp = pci_devices; i < pci_count; i++, busp++) {
		pci_childcount = 0;
		if (device_get_children(*busp, &pci_children, &pci_childcount))
			continue;
		for (j = 0, childp = pci_children; j < pci_childcount; j++, childp++) {
			if (pci_get_vendor(*childp) == 0x8086 && pci_get_device(*childp) == 0x7113) {
				port = (pci_read_config(*childp, 0x41, 1) << 8) + 0x10;
				/* XXX */
				btag = X86_BUS_SPACE_IO;

				control = bus_space_read_2(btag, 0x0, port);
				control &= ~0x2000;
				control |= run? 0 : 0x2000;
				bus_space_write_2(btag, 0x0, port, control);
				free(pci_devices, M_TEMP);
				free(pci_children, M_TEMP);
				return 0;
			}
		}
		free(pci_children, M_TEMP);
	}

	free(pci_devices, M_TEMP);
	return ENXIO;
#else
	return 0;
#endif
}