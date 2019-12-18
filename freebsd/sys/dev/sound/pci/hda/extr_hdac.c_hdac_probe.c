#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  desc ;
struct TYPE_3__ {int model; char* desc; } ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int BUS_PROBE_GENERIC ; 
 int ENXIO ; 
 scalar_t__ HDA_DEV_MATCH (int,int) ; 
 scalar_t__ PCIC_MULTIMEDIA ; 
 scalar_t__ PCIS_MULTIMEDIA_HDA ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* hdac_devices ; 
 int nitems (TYPE_1__*) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static int
hdac_probe(device_t dev)
{
	int i, result;
	uint32_t model;
	uint16_t class, subclass;
	char desc[64];

	model = (uint32_t)pci_get_device(dev) << 16;
	model |= (uint32_t)pci_get_vendor(dev) & 0x0000ffff;
	class = pci_get_class(dev);
	subclass = pci_get_subclass(dev);

	bzero(desc, sizeof(desc));
	result = ENXIO;
	for (i = 0; i < nitems(hdac_devices); i++) {
		if (hdac_devices[i].model == model) {
			strlcpy(desc, hdac_devices[i].desc, sizeof(desc));
			result = BUS_PROBE_DEFAULT;
			break;
		}
		if (HDA_DEV_MATCH(hdac_devices[i].model, model) &&
		    class == PCIC_MULTIMEDIA &&
		    subclass == PCIS_MULTIMEDIA_HDA) {
			snprintf(desc, sizeof(desc),
			    "%s (0x%04x)",
			    hdac_devices[i].desc, pci_get_device(dev));
			result = BUS_PROBE_GENERIC;
			break;
		}
	}
	if (result == ENXIO && class == PCIC_MULTIMEDIA &&
	    subclass == PCIS_MULTIMEDIA_HDA) {
		snprintf(desc, sizeof(desc), "Generic (0x%08x)", model);
		result = BUS_PROBE_GENERIC;
	}
	if (result != ENXIO) {
		strlcat(desc, " HDA Controller", sizeof(desc));
		device_set_desc_copy(dev, desc);
	}

	return (result);
}