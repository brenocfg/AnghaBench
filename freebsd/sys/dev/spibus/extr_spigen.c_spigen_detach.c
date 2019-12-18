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
struct spigen_softc {int /*<<< orphan*/  sc_mtx; scalar_t__ sc_cdev; scalar_t__ sc_adev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_dev (scalar_t__) ; 
 struct spigen_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
spigen_detach(device_t dev)
{
	struct spigen_softc *sc;

	sc = device_get_softc(dev);

#ifdef SPIGEN_LEGACY_CDEVNAME
	if (sc->sc_adev)
		destroy_dev(sc->sc_adev);
#endif

	if (sc->sc_cdev)
		destroy_dev(sc->sc_cdev);
	
	mtx_destroy(&sc->sc_mtx);

	return (0);
}