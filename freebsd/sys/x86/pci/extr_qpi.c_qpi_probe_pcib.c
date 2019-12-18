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
typedef  int uint32_t ;
struct qpi_device {int qd_pcibus; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int EEXIST ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_QPI ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PCIR_DEVVENDOR ; 
 int PCI_SLOTMAX ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct qpi_device*) ; 
 struct qpi_device* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int) ; 
 int pci_cfgregread (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pci_find_bsf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qpi_probe_pcib(device_t dev, int bus)
{
	struct qpi_device *qdev;
	device_t child;
	uint32_t devid;
	int s;

	/*
	 * If a PCI bus already exists for this bus number, then
	 * fail.
	 */
	if (pci_find_bsf(bus, 0, 0) != NULL)
		return (EEXIST);

	/*
	 * Attempt to read the device id for every slot, function 0 on
	 * the bus.  If all read values are 0xffffffff this means that
	 * the bus is not present.
	 */
	for (s = 0; s <= PCI_SLOTMAX; s++) {
		devid = pci_cfgregread(bus, s, 0, PCIR_DEVVENDOR, 4);
		if (devid != 0xffffffff)
			break;
	}
	if (devid == 0xffffffff)
		return (ENOENT);

	if ((devid & 0xffff) != 0x8086) {
		if (bootverbose)
			device_printf(dev,
			    "Device at pci%d.%d.0 has non-Intel vendor 0x%x\n",
			    bus, s, devid & 0xffff);
		return (ENXIO);
	}

	child = BUS_ADD_CHILD(dev, 0, "pcib", -1);
	if (child == NULL)
		panic("%s: failed to add pci bus %d", device_get_nameunit(dev),
		    bus);
	qdev = malloc(sizeof(struct qpi_device), M_QPI, M_WAITOK);
	qdev->qd_pcibus = bus;
	device_set_ivars(child, qdev);
	return (0);
}