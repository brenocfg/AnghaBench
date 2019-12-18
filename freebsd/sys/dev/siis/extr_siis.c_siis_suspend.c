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
struct siis_controller {int /*<<< orphan*/  gctl; int /*<<< orphan*/  r_gmem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIIS_GCTL ; 
 int /*<<< orphan*/  SIIS_GCTL_GRESET ; 
 int /*<<< orphan*/  bus_generic_suspend (int /*<<< orphan*/ ) ; 
 struct siis_controller* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
siis_suspend(device_t dev)
{
	struct siis_controller *ctlr = device_get_softc(dev);

	bus_generic_suspend(dev);
	/* Put controller into reset state. */
	ctlr->gctl |= SIIS_GCTL_GRESET;
	ATA_OUTL(ctlr->r_gmem, SIIS_GCTL, ctlr->gctl);
	return 0;
}