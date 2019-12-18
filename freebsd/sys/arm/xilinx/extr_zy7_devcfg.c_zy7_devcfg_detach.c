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
struct zy7_devcfg_softc {int /*<<< orphan*/ * mem_res; int /*<<< orphan*/ * irq_res; scalar_t__ intrhandle; int /*<<< orphan*/ * sc_ctl_dev; int /*<<< orphan*/ * sysctl_tree_top; int /*<<< orphan*/  sysctl_tree; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCFG_SC_LOCK_DESTROY (struct zy7_devcfg_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 struct zy7_devcfg_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zy7_devcfg_softc_p ; 

__attribute__((used)) static int
zy7_devcfg_detach(device_t dev)
{
	struct zy7_devcfg_softc *sc = device_get_softc(dev);

	if (sc->sysctl_tree_top != NULL) {
		sysctl_ctx_free(&sc->sysctl_tree);
		sc->sysctl_tree_top = NULL;
	}

	if (device_is_attached(dev))
		bus_generic_detach(dev);

	/* Get rid of /dev/devcfg0. */
	if (sc->sc_ctl_dev != NULL)
		destroy_dev(sc->sc_ctl_dev);

	/* Teardown and release interrupt. */
	if (sc->irq_res != NULL) {
		if (sc->intrhandle)
			bus_teardown_intr(dev, sc->irq_res, sc->intrhandle);
		bus_release_resource(dev, SYS_RES_IRQ,
			     rman_get_rid(sc->irq_res), sc->irq_res);
	}

	/* Release memory resource. */
	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY,
			     rman_get_rid(sc->mem_res), sc->mem_res);

	zy7_devcfg_softc_p = NULL;

	DEVCFG_SC_LOCK_DESTROY(sc);

	return (0);
}