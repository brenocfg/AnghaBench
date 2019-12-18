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
struct amdvi_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  amdvi_add_sysctl (struct amdvi_softc*) ; 
 int amdvi_alloc_intr_resources (struct amdvi_softc*) ; 
 int /*<<< orphan*/  amdvi_hw_enable_iotlb (struct amdvi_softc*) ; 
 int amdvi_init_cmd (struct amdvi_softc*) ; 
 int amdvi_init_dte (struct amdvi_softc*) ; 
 int amdvi_init_event (struct amdvi_softc*) ; 
 int /*<<< orphan*/  amdvi_print_dev_cap (struct amdvi_softc*) ; 
 int amdvi_print_pci_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

int
amdvi_setup_hw(struct amdvi_softc *softc)
{
	device_t dev;
	int status;

	dev = softc->dev;

	amdvi_hw_enable_iotlb(softc);

	amdvi_print_dev_cap(softc);

	if ((status = amdvi_print_pci_cap(dev)) != 0) {
		device_printf(dev, "PCI capability.\n");
		return (status);
	}
	if ((status = amdvi_init_cmd(softc)) != 0) {
		device_printf(dev, "Couldn't configure command buffer.\n");
		return (status);
	}
	if ((status = amdvi_init_event(softc)) != 0) {
		device_printf(dev, "Couldn't configure event buffer.\n");
		return (status);
	}
	if ((status = amdvi_init_dte(softc)) != 0) {
		device_printf(dev, "Couldn't configure device table.\n");
		return (status);
	}
	if ((status = amdvi_alloc_intr_resources(softc)) != 0) {
		return (status);
	}
	amdvi_add_sysctl(softc);
	return (0);
}