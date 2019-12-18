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
struct sbni_softc {scalar_t__ slave_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 struct sbni_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbni_detach (struct sbni_softc*) ; 
 int /*<<< orphan*/  sbni_release_resources (struct sbni_softc*) ; 

__attribute__((used)) static int
sbni_pci_detach(device_t dev)
{
	struct sbni_softc *sc;

	sc = device_get_softc(dev);
	sbni_detach(sc);
	if (sc->slave_sc)
		sbni_detach(sc);
	
	sbni_release_resources(sc);
	if (sc->slave_sc)
		free(sc->slave_sc, M_DEVBUF);
	return (0);
}