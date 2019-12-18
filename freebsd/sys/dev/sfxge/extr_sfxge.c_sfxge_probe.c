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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int efx_family_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*,int,...) ; 
 int EFX_FAMILY_HUNTINGTON ; 
 int EFX_FAMILY_MEDFORD ; 
 int EFX_FAMILY_MEDFORD2 ; 
 int EFX_FAMILY_SIENA ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int efx_family (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,unsigned int*) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sfxge_probe(device_t dev)
{
	uint16_t pci_vendor_id;
	uint16_t pci_device_id;
	efx_family_t family;
	unsigned int mem_bar;
	int rc;

	pci_vendor_id = pci_get_vendor(dev);
	pci_device_id = pci_get_device(dev);

	DBGPRINT(dev, "PCI ID %04x:%04x", pci_vendor_id, pci_device_id);
	rc = efx_family(pci_vendor_id, pci_device_id, &family, &mem_bar);
	if (rc != 0) {
		DBGPRINT(dev, "efx_family fail %d", rc);
		return (ENXIO);
	}

	if (family == EFX_FAMILY_SIENA) {
		device_set_desc(dev, "Solarflare SFC9000 family");
		return (0);
	}

	if (family == EFX_FAMILY_HUNTINGTON) {
		device_set_desc(dev, "Solarflare SFC9100 family");
		return (0);
	}

	if (family == EFX_FAMILY_MEDFORD) {
		device_set_desc(dev, "Solarflare SFC9200 family");
		return (0);
	}

	if (family == EFX_FAMILY_MEDFORD2) {
		device_set_desc(dev, "Solarflare SFC9250 family");
		return (0);
	}

	DBGPRINT(dev, "impossible controller family %d", family);
	return (ENXIO);
}