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
struct gpioc_softc {scalar_t__ sc_ctl_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_dev (scalar_t__) ; 
 struct gpioc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gpioc_detach(device_t dev)
{
	struct gpioc_softc *sc = device_get_softc(dev);
	int err;

	if (sc->sc_ctl_dev)
		destroy_dev(sc->sc_ctl_dev);

	if ((err = bus_generic_detach(dev)) != 0)
		return (err);

	return (0);
}