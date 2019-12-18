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
struct ahd_softc {int /*<<< orphan*/  dev_softc; TYPE_1__* platform_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  ih; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 int /*<<< orphan*/  ahd_platform_intr ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ahd_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

int
ahd_map_int(struct ahd_softc *ahd)
{
	int error;

	/* Hook up our interrupt handler */
	error = bus_setup_intr(ahd->dev_softc, ahd->platform_data->irq,
			       INTR_TYPE_CAM|INTR_MPSAFE, NULL,
			       ahd_platform_intr, ahd, &ahd->platform_data->ih);
	if (error != 0)
		device_printf(ahd->dev_softc, "bus_setup_intr() failed: %d\n",
			      error);
	return (error);
}