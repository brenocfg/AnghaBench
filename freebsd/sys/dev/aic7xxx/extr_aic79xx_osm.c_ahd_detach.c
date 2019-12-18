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
struct ahd_softc {TYPE_1__* platform_data; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  ih; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_free (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_intr_enable (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_lock (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_tailq ; 
 int /*<<< orphan*/  ahd_unlock (struct ahd_softc*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ahd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  links ; 

int
ahd_detach(device_t dev)
{
	struct ahd_softc *ahd;

	device_printf(dev, "detaching device\n");
	ahd = device_get_softc(dev);
	ahd_lock(ahd);
	TAILQ_REMOVE(&ahd_tailq, ahd, links);
	ahd_intr_enable(ahd, FALSE);
	bus_teardown_intr(dev, ahd->platform_data->irq, ahd->platform_data->ih);
	ahd_unlock(ahd);
	ahd_free(ahd);
	return (0);
}