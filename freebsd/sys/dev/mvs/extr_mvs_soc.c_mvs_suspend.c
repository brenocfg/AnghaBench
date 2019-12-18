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
struct mvs_controller {int /*<<< orphan*/  r_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CHIP_SOC_MIM ; 
 int /*<<< orphan*/  bus_generic_suspend (int /*<<< orphan*/ ) ; 
 struct mvs_controller* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mvs_suspend(device_t dev)
{
	struct mvs_controller *ctlr = device_get_softc(dev);

	bus_generic_suspend(dev);
	/* Mask chip interrupts */
	ATA_OUTL(ctlr->r_mem, CHIP_SOC_MIM, 0x00000000);
	return 0;
}