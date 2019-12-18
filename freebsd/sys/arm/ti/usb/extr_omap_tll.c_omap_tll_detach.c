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
struct omap_tll_softc {int /*<<< orphan*/ * tll_mem_res; int /*<<< orphan*/  tll_mem_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct omap_tll_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_tll_disable (struct omap_tll_softc*) ; 
 int /*<<< orphan*/ * omap_tll_sc ; 

__attribute__((used)) static int
omap_tll_detach(device_t dev)
{
	struct omap_tll_softc *sc;

	sc = device_get_softc(dev);
	omap_tll_disable(sc);

	/* Release the other register set memory maps */
	if (sc->tll_mem_res) {
		bus_release_resource(dev, SYS_RES_MEMORY,
		    sc->tll_mem_rid, sc->tll_mem_res);
		sc->tll_mem_res = NULL;
	}

	omap_tll_sc = NULL;

	return (0);
}