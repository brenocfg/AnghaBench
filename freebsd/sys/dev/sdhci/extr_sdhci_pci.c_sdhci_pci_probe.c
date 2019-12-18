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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int model; int subvendor; char* desc; } ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int BUS_PROBE_GENERIC ; 
 int ENXIO ; 
 scalar_t__ PCIC_BASEPERIPH ; 
 scalar_t__ PCIS_BASEPERIPH_SDHC ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 
 int pci_get_subvendor (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 TYPE_1__* sdhci_devices ; 

__attribute__((used)) static int
sdhci_pci_probe(device_t dev)
{
	uint32_t model;
	uint16_t subvendor;
	uint8_t class, subclass;
	int i, result;

	model = (uint32_t)pci_get_device(dev) << 16;
	model |= (uint32_t)pci_get_vendor(dev) & 0x0000ffff;
	subvendor = pci_get_subvendor(dev);
	class = pci_get_class(dev);
	subclass = pci_get_subclass(dev);

	result = ENXIO;
	for (i = 0; sdhci_devices[i].model != 0; i++) {
		if (sdhci_devices[i].model == model &&
		    (sdhci_devices[i].subvendor == 0xffff ||
		    sdhci_devices[i].subvendor == subvendor)) {
			device_set_desc(dev, sdhci_devices[i].desc);
			result = BUS_PROBE_DEFAULT;
			break;
		}
	}
	if (result == ENXIO && class == PCIC_BASEPERIPH &&
	    subclass == PCIS_BASEPERIPH_SDHC) {
		device_set_desc(dev, "Generic SD HCI");
		result = BUS_PROBE_GENERIC;
	}

	return (result);
}