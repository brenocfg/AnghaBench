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

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
#define  MAESTRO_1_PCI_ID 130 
#define  MAESTRO_2E_PCI_ID 129 
#define  MAESTRO_2_PCI_ID 128 
 scalar_t__ PCIC_MULTIMEDIA ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agg_probe(device_t dev)
{
	char *s = NULL;

	switch (pci_get_devid(dev)) {
	case MAESTRO_1_PCI_ID:
		s = "ESS Technology Maestro-1";
		break;

	case MAESTRO_2_PCI_ID:
		s = "ESS Technology Maestro-2";
		break;

	case MAESTRO_2E_PCI_ID:
		s = "ESS Technology Maestro-2E";
		break;
	}

	if (s != NULL && pci_get_class(dev) == PCIC_MULTIMEDIA) {
		device_set_desc(dev, s);
		return BUS_PROBE_DEFAULT;
	}
	return ENXIO;
}