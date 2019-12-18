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
struct amdvi_softc {int iotlb; int ivhd_flag; int pci_cap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AMDVI_PCI_CAP_IOTLB ; 
 int IVHD_FLAG_IOTLB ; 
 int /*<<< orphan*/  amdvi_enable_iotlb ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline void
amdvi_hw_enable_iotlb(struct amdvi_softc *softc)
{
#ifndef AMDVI_ATS_ENABLE
	softc->iotlb = false;
#else
	bool supported;

	supported = (softc->ivhd_flag & IVHD_FLAG_IOTLB) ? true : false;

	if (softc->pci_cap & AMDVI_PCI_CAP_IOTLB) {
		if (!supported)
			device_printf(softc->dev, "IOTLB disabled by BIOS.\n");

		if (supported && !amdvi_enable_iotlb) {
			device_printf(softc->dev, "IOTLB disabled by user.\n");
			supported = false;
		}
	} else
		supported = false;

	softc->iotlb = supported;

#endif
}