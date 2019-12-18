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
struct pps_softc {TYPE_1__* gpin; int /*<<< orphan*/ * ires; int /*<<< orphan*/  irid; int /*<<< orphan*/ * ihandler; int /*<<< orphan*/ * pps_cdev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  pin; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_GET_BUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 struct pps_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_release_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gpiopps_detach(device_t dev)
{
	struct pps_softc *sc = device_get_softc(dev);

	if (sc->pps_cdev != NULL)
		destroy_dev(sc->pps_cdev);
	if (sc->ihandler != NULL)
		bus_teardown_intr(dev, sc->ires, sc->ihandler);
	if (sc->ires != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, sc->irid, sc->ires);
	if (sc->gpin != NULL)
		gpiobus_release_pin(GPIO_GET_BUS(sc->gpin->dev), sc->gpin->pin);
	return (0);
}