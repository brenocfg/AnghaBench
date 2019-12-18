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
struct siis_controller {int gctl; int /*<<< orphan*/  r_gmem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  SIIS_GCTL ; 
 int SIIS_GCTL_GRESET ; 
 int SIIS_GCTL_I2C_IE ; 
 int bus_generic_resume (int /*<<< orphan*/ ) ; 
 struct siis_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_get_max_read_req (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_max_read_req (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
siis_resume(device_t dev)
{
	struct siis_controller *ctlr = device_get_softc(dev);

	/* Set PCIe max read request size to at least 1024 bytes */
	if (pci_get_max_read_req(dev) < 1024)
		pci_set_max_read_req(dev, 1024);
	/* Put controller into reset state. */
	ctlr->gctl |= SIIS_GCTL_GRESET;
	ATA_OUTL(ctlr->r_gmem, SIIS_GCTL, ctlr->gctl);
	DELAY(10000);
	/* Get controller out of reset state and enable port interrupts. */
	ctlr->gctl &= ~(SIIS_GCTL_GRESET | SIIS_GCTL_I2C_IE);
	ctlr->gctl |= 0x0000000f;
	ATA_OUTL(ctlr->r_gmem, SIIS_GCTL, ctlr->gctl);
	return (bus_generic_resume(dev));
}