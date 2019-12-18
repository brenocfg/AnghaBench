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
struct mgb_softc {int /*<<< orphan*/ * pba; int /*<<< orphan*/  dev; int /*<<< orphan*/ * miibus; int /*<<< orphan*/  admin_irq; int /*<<< orphan*/  rx_irq; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mgb_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_irq_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mgb_hw_teardown (struct mgb_softc*) ; 
 int mgb_release_regs (struct mgb_softc*) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mgb_detach(if_ctx_t ctx)
{
	struct mgb_softc *sc;
	int error;

	sc = iflib_get_softc(ctx);

	/* XXX: Should report errors but still detach everything. */
	error = mgb_hw_teardown(sc);

	/* Release IRQs */
	iflib_irq_free(ctx, &sc->rx_irq);
	iflib_irq_free(ctx, &sc->admin_irq);

	if (sc->miibus != NULL)
		device_delete_child(sc->dev, sc->miibus);

	if (sc->pba != NULL)
		error = bus_release_resource(sc->dev, SYS_RES_MEMORY,
		    rman_get_rid(sc->pba), sc->pba);
	sc->pba = NULL;

	error = mgb_release_regs(sc);

	return (error);
}