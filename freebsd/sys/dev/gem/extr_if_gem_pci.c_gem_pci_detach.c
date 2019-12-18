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
struct gem_softc {int /*<<< orphan*/ * sc_res; int /*<<< orphan*/  sc_ih; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_LOCK_DESTROY (struct gem_softc*) ; 
 size_t GEM_RES_BANK2 ; 
 size_t GEM_RES_INTR ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gem_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gem_detach (struct gem_softc*) ; 
 int /*<<< orphan*/  gem_pci_res_spec ; 

__attribute__((used)) static int
gem_pci_detach(device_t dev)
{
	struct gem_softc *sc;

	sc = device_get_softc(dev);
	bus_teardown_intr(dev, sc->sc_res[GEM_RES_INTR], sc->sc_ih);
	gem_detach(sc);
	free(sc->sc_res[GEM_RES_BANK2], M_DEVBUF);
	GEM_LOCK_DESTROY(sc);
	bus_release_resources(dev, gem_pci_res_spec, sc->sc_res);
	return (0);
}