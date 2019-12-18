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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct aac_softc {int /*<<< orphan*/  aac_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ PCICAP_ID ; 
 scalar_t__ PCICAP_NEXTPTR ; 
 int PCIM_HDRTYPE ; 
 int PCIM_STATUS_CAPPRESENT ; 
 scalar_t__ PCIR_CAP_PTR ; 
 scalar_t__ PCIR_CAP_PTR_2 ; 
 scalar_t__ PCIR_HDRTYPE ; 
 scalar_t__ PCIR_STATUS ; 
 void* pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int
aac_find_pci_capability(struct aac_softc *sc, int cap)
{
	device_t dev;
	uint32_t status;
	uint8_t ptr;

	dev = sc->aac_dev;

	status = pci_read_config(dev, PCIR_STATUS, 2);
	if (!(status & PCIM_STATUS_CAPPRESENT))
		return (0);

	status = pci_read_config(dev, PCIR_HDRTYPE, 1);
	switch (status & PCIM_HDRTYPE) {
	case 0:
	case 1:
		ptr = PCIR_CAP_PTR;
		break;
	case 2:
		ptr = PCIR_CAP_PTR_2;
		break;
	default:
		return (0);
		break;
	}
	ptr = pci_read_config(dev, ptr, 1);

	while (ptr != 0) {
		int next, val;
		next = pci_read_config(dev, ptr + PCICAP_NEXTPTR, 1);
		val = pci_read_config(dev, ptr + PCICAP_ID, 1);
		if (val == cap)
			return (ptr);
		ptr = next;
	}

	return (0);
}