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
struct agp_softc {int as_aperture_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct agp_softc* device_get_softc (int /*<<< orphan*/ ) ; 

void
agp_set_aperture_resource(device_t dev, int rid)
{
	struct agp_softc *sc = device_get_softc(dev);

	sc->as_aperture_rid = rid;
}