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
struct agp_i810_softc {TYPE_1__* gatt; int /*<<< orphan*/ * sc_res; int /*<<< orphan*/  initial_aperture; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int ag_physical; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_I810_PGTBL_CTL ; 
 int /*<<< orphan*/  AGP_SET_APERTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_generic_resume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_i810_resume(device_t dev)
{
	struct agp_i810_softc *sc;
	sc = device_get_softc(dev);

	AGP_SET_APERTURE(dev, sc->initial_aperture);

	/* Install the GATT. */
	bus_write_4(sc->sc_res[0], AGP_I810_PGTBL_CTL,
	sc->gatt->ag_physical | 1);

	return (bus_generic_resume(dev));
}