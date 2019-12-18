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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_get_subdevice (int /*<<< orphan*/ ) ; 
 int pci_get_subvendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ess_probe(device_t dev)
{
	char *s = NULL;
	u_int32_t subdev;

	subdev = (pci_get_subdevice(dev) << 16) | pci_get_subvendor(dev);
	switch (pci_get_devid(dev)) {
	case 0x1969125d:
		if (subdev == 0x8888125d)
			s = "ESS Solo-1E";
		else if (subdev == 0x1818125d)
			s = "ESS Solo-1";
		else
			s = "ESS Solo-1 (unknown vendor)";
		break;
	}

	if (s)
		device_set_desc(dev, s);
	return s ? BUS_PROBE_DEFAULT : ENXIO;
}