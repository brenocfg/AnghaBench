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
struct qman_softc {int /*<<< orphan*/ * sc_rres; int /*<<< orphan*/  sc_rrid; int /*<<< orphan*/ * sc_ires; int /*<<< orphan*/  sc_irid; scalar_t__ sc_qh; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  QM_Free (scalar_t__) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  XX_DeallocIntr (uintptr_t) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct qman_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
qman_detach(device_t dev)
{
	struct qman_softc *sc;

	sc = device_get_softc(dev);

	if (sc->sc_qh)
		QM_Free(sc->sc_qh);

	if (sc->sc_ires != NULL)
		XX_DeallocIntr((uintptr_t)sc->sc_ires);

	if (sc->sc_ires != NULL)
		bus_release_resource(dev, SYS_RES_IRQ,
		    sc->sc_irid, sc->sc_ires);

	if (sc->sc_rres != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    sc->sc_rrid, sc->sc_rres);

	return (0);
}