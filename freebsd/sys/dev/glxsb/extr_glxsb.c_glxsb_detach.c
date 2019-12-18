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
struct glxsb_softc {int /*<<< orphan*/  sc_task_mtx; int /*<<< orphan*/  sc_tq; int /*<<< orphan*/  sc_sr; int /*<<< orphan*/  sc_rid; int /*<<< orphan*/  sc_dma; int /*<<< orphan*/  sc_cryptotask; int /*<<< orphan*/  sc_rngco; int /*<<< orphan*/  sc_cid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_all (int /*<<< orphan*/ ) ; 
 struct glxsb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glxsb_dma_free (struct glxsb_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
glxsb_detach(device_t dev)
{
	struct glxsb_softc *sc = device_get_softc(dev);

	crypto_unregister_all(sc->sc_cid);

	callout_drain(&sc->sc_rngco);
	taskqueue_drain(sc->sc_tq, &sc->sc_cryptotask);
	bus_generic_detach(dev);
	glxsb_dma_free(sc, &sc->sc_dma);
	bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_rid, sc->sc_sr);
	taskqueue_free(sc->sc_tq);
	mtx_destroy(&sc->sc_task_mtx);
	return (0);
}