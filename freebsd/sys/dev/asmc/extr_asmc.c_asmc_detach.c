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
struct asmc_softc {int /*<<< orphan*/  sc_mtx; scalar_t__ sc_ioport; int /*<<< orphan*/  sc_rid_port; scalar_t__ sc_irq; int /*<<< orphan*/  sc_rid_irq; scalar_t__ sc_cookie; scalar_t__ sc_sms_tq; int /*<<< orphan*/  sc_sms_task; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct asmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (scalar_t__) ; 

__attribute__((used)) static int
asmc_detach(device_t dev)
{
	struct asmc_softc *sc = device_get_softc(dev);

	if (sc->sc_sms_tq) {
		taskqueue_drain(sc->sc_sms_tq, &sc->sc_sms_task);
		taskqueue_free(sc->sc_sms_tq);
	}
	if (sc->sc_cookie)
		bus_teardown_intr(dev, sc->sc_irq, sc->sc_cookie);
	if (sc->sc_irq)
		bus_release_resource(dev, SYS_RES_IRQ, sc->sc_rid_irq,
		    sc->sc_irq);
	if (sc->sc_ioport)
		bus_release_resource(dev, SYS_RES_IOPORT, sc->sc_rid_port,
		    sc->sc_ioport);
	mtx_destroy(&sc->sc_mtx);

	return (0);
}