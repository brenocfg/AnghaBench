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
struct omap4_prcm_softc {int sc_instance; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/  devclass_get_device (int /*<<< orphan*/ ,int) ; 
 int devclass_get_maxunit (int /*<<< orphan*/ ) ; 
 struct omap4_prcm_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct omap4_prcm_softc *
omap4_prcm_get_instance_softc(int module_instance)
{
	int i, maxunit;
	devclass_t prcm_devclass;
	device_t dev;
	struct omap4_prcm_softc *sc;

	prcm_devclass = devclass_find("omap4_prcm");
	maxunit = devclass_get_maxunit(prcm_devclass);

	for (i = 0; i < maxunit; i++) {
		dev = devclass_get_device(prcm_devclass, i);
		sc = device_get_softc(dev);
		if (sc->sc_instance == module_instance)
			return (sc);
	}

	return (NULL);
}