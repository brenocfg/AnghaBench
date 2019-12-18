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
struct ahc_softc {TYPE_1__* platform_data; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  ih; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_free (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_intr_enable (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_lock (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_tailq ; 
 int /*<<< orphan*/  ahc_unlock (struct ahc_softc*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ahc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  links ; 

int
ahc_detach(device_t dev)
{
	struct ahc_softc *ahc;

	device_printf(dev, "detaching device\n");
	ahc = device_get_softc(dev);
	ahc_lock(ahc);
	TAILQ_REMOVE(&ahc_tailq, ahc, links);
	ahc_intr_enable(ahc, FALSE);
	bus_teardown_intr(dev, ahc->platform_data->irq, ahc->platform_data->ih);
	ahc_unlock(ahc);
	ahc_free(ahc);
	return (0);
}