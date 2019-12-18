#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  q_ctx; int /*<<< orphan*/  q_mcr; } ;
struct TYPE_6__ {int /*<<< orphan*/  rng_buf; TYPE_2__ rng_q; } ;
struct ubsec_softc {int sc_flags; int /*<<< orphan*/  sc_sr; int /*<<< orphan*/  sc_dmat; int /*<<< orphan*/  sc_irq; int /*<<< orphan*/  sc_ih; int /*<<< orphan*/  sc_mcr2lock; TYPE_3__ sc_rng; int /*<<< orphan*/  sc_freeqlock; int /*<<< orphan*/  sc_mcr1lock; int /*<<< orphan*/  sc_freequeue; scalar_t__ sc_rndtest; int /*<<< orphan*/  sc_cid; int /*<<< orphan*/  sc_rngto; } ;
struct ubsec_q {TYPE_1__* q_dma; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/  d_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BS_BAR ; 
 int /*<<< orphan*/  BS_CTRL ; 
 int BS_CTRL_DMAERR ; 
 int BS_CTRL_MCR1INT ; 
 int BS_CTRL_MCR2INT ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int READ_REG (struct ubsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIMPLEQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct ubsec_q* SIMPLEQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIMPLEQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int UBS_FLAGS_RNG ; 
 int /*<<< orphan*/  WRITE_REG (struct ubsec_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_all (int /*<<< orphan*/ ) ; 
 struct ubsec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ubsec_q*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  q_next ; 
 int /*<<< orphan*/  rndtest_detach (scalar_t__) ; 
 int /*<<< orphan*/  ubsec_dma_free (struct ubsec_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ubsec_detach(device_t dev)
{
	struct ubsec_softc *sc = device_get_softc(dev);

	/* XXX wait/abort active ops */

	/* disable interrupts */
	WRITE_REG(sc, BS_CTRL, READ_REG(sc, BS_CTRL) &~
		(BS_CTRL_MCR2INT | BS_CTRL_MCR1INT | BS_CTRL_DMAERR));

	callout_stop(&sc->sc_rngto);

	crypto_unregister_all(sc->sc_cid);

#ifdef UBSEC_RNDTEST
	if (sc->sc_rndtest)
		rndtest_detach(sc->sc_rndtest);
#endif

	while (!SIMPLEQ_EMPTY(&sc->sc_freequeue)) {
		struct ubsec_q *q;

		q = SIMPLEQ_FIRST(&sc->sc_freequeue);
		SIMPLEQ_REMOVE_HEAD(&sc->sc_freequeue, q_next);
		ubsec_dma_free(sc, &q->q_dma->d_alloc);
		free(q, M_DEVBUF);
	}
	mtx_destroy(&sc->sc_mcr1lock);
	mtx_destroy(&sc->sc_freeqlock);
#ifndef UBSEC_NO_RNG
	if (sc->sc_flags & UBS_FLAGS_RNG) {
		ubsec_dma_free(sc, &sc->sc_rng.rng_q.q_mcr);
		ubsec_dma_free(sc, &sc->sc_rng.rng_q.q_ctx);
		ubsec_dma_free(sc, &sc->sc_rng.rng_buf);
	}
#endif /* UBSEC_NO_RNG */
	mtx_destroy(&sc->sc_mcr2lock);

	bus_generic_detach(dev);
	bus_teardown_intr(dev, sc->sc_irq, sc->sc_ih);
	bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_irq);

	bus_dma_tag_destroy(sc->sc_dmat);
	bus_release_resource(dev, SYS_RES_MEMORY, BS_BAR, sc->sc_sr);

	return (0);
}