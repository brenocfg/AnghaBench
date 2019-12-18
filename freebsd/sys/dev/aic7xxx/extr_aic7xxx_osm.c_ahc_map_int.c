#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ahc_softc {int flags; int /*<<< orphan*/  dev_softc; TYPE_1__* platform_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  ih; int /*<<< orphan*/ * irq; int /*<<< orphan*/  irq_res_type; } ;

/* Variables and functions */
 int AHC_EDGE_INTERRUPT ; 
 int ENOMEM ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  ahc_platform_intr ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ahc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

int
ahc_map_int(struct ahc_softc *ahc)
{
	int error;
	int zero;
	int shareable;

	zero = 0;
	shareable = (ahc->flags & AHC_EDGE_INTERRUPT) ? 0: RF_SHAREABLE;
	ahc->platform_data->irq =
	    bus_alloc_resource_any(ahc->dev_softc, SYS_RES_IRQ, &zero,
				   RF_ACTIVE | shareable);
	if (ahc->platform_data->irq == NULL) {
		device_printf(ahc->dev_softc,
			      "bus_alloc_resource() failed to allocate IRQ\n");
		return (ENOMEM);
	}
	ahc->platform_data->irq_res_type = SYS_RES_IRQ;

	/* Hook up our interrupt handler */
	error = bus_setup_intr(ahc->dev_softc, ahc->platform_data->irq,
			       INTR_TYPE_CAM|INTR_MPSAFE, NULL, 
			       ahc_platform_intr, ahc, &ahc->platform_data->ih);

	if (error != 0)
		device_printf(ahc->dev_softc, "bus_setup_intr() failed: %d\n",
			      error);
	return (error);
}