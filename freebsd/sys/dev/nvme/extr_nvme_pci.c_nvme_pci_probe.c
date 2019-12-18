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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct nvme_controller {int /*<<< orphan*/  quirks; } ;
struct _pcsid {char* desc; int /*<<< orphan*/  quirks; scalar_t__ devid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int BUS_PROBE_GENERIC ; 
 struct nvme_controller* DEVICE2SOFTC (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 scalar_t__ PCIC_STORAGE ; 
 scalar_t__ PCIP_STORAGE_NVM_ENTERPRISE_NVMHCI_1_0 ; 
 scalar_t__ PCIS_STORAGE_NVM ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvme_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct _pcsid*) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_progif (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subdevice (int /*<<< orphan*/ ) ; 
 struct _pcsid* pci_ids ; 

__attribute__((used)) static int
nvme_pci_probe (device_t device)
{
	struct nvme_controller *ctrlr = DEVICE2SOFTC(device);
	struct _pcsid	*ep;
	uint32_t	devid;
	uint16_t	subdevice;

	devid = pci_get_devid(device);
	subdevice = pci_get_subdevice(device);
	ep = pci_ids;

	while (ep->devid) {
		if (nvme_match(devid, subdevice, ep))
			break;
		++ep;
	}
	if (ep->devid)
		ctrlr->quirks = ep->quirks;

	if (ep->desc) {
		device_set_desc(device, ep->desc);
		return (BUS_PROBE_DEFAULT);
	}

#if defined(PCIS_STORAGE_NVM)
	if (pci_get_class(device)    == PCIC_STORAGE &&
	    pci_get_subclass(device) == PCIS_STORAGE_NVM &&
	    pci_get_progif(device)   == PCIP_STORAGE_NVM_ENTERPRISE_NVMHCI_1_0) {
		device_set_desc(device, "Generic NVMe Device");
		return (BUS_PROBE_GENERIC);
	}
#endif

	return (ENXIO);
}