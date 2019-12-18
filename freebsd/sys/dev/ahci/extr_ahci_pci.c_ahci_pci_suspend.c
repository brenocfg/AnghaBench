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
struct ahci_controller {int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_GHC ; 
 int AHCI_GHC_IE ; 
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_generic_suspend (int /*<<< orphan*/ ) ; 
 struct ahci_controller* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ahci_pci_suspend(device_t dev)
{
	struct ahci_controller *ctlr = device_get_softc(dev);

	bus_generic_suspend(dev);
	/* Disable interupts, so the state change(s) doesn't trigger */
	ATA_OUTL(ctlr->r_mem, AHCI_GHC,
	     ATA_INL(ctlr->r_mem, AHCI_GHC) & (~AHCI_GHC_IE));
	return 0;
}