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
struct cas_softc {int /*<<< orphan*/ * sc_res; int /*<<< orphan*/  sc_ih; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAS_LOCK_DESTROY (struct cas_softc*) ; 
 size_t CAS_RES_INTR ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_detach (struct cas_softc*) ; 
 int /*<<< orphan*/  cas_pci_res_spec ; 
 struct cas_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cas_pci_detach(device_t dev)
{
	struct cas_softc *sc;

	sc = device_get_softc(dev);
	bus_teardown_intr(dev, sc->sc_res[CAS_RES_INTR], sc->sc_ih);
	cas_detach(sc);
	CAS_LOCK_DESTROY(sc);
	bus_release_resources(dev, cas_pci_res_spec, sc->sc_res);
	return (0);
}