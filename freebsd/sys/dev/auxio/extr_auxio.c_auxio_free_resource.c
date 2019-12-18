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
struct auxio_softc {int sc_nauxio; scalar_t__* sc_res; int /*<<< orphan*/ * sc_rid; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUXIO_LOCK_DESTROY (struct auxio_softc*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
auxio_free_resource(struct auxio_softc *sc)
{
	int i;

	for (i = 0; i < sc->sc_nauxio; i++)
		if (sc->sc_res[i])
			bus_release_resource(sc->sc_dev, SYS_RES_MEMORY,
			    sc->sc_rid[i], sc->sc_res[i]);
	AUXIO_LOCK_DESTROY(sc);
}