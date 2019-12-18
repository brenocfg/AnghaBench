#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mwl_softc {scalar_t__ sc_nrxfree; int /*<<< orphan*/  sc_imask; int /*<<< orphan*/  sc_mh; scalar_t__ sc_rxblocked; } ;
struct TYPE_2__ {int /*<<< orphan*/  ext_buf; struct mwl_softc* ext_arg1; } ;
struct mbuf {TYPE_1__ m_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwl_hal_intrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl_putrxdma (struct mwl_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ mwl_rxdmalow ; 

__attribute__((used)) static void
mwl_ext_free(struct mbuf *m)
{
	struct mwl_softc *sc = m->m_ext.ext_arg1;

	/* XXX bounds check data */
	mwl_putrxdma(sc, m->m_ext.ext_buf);
	/*
	 * If we were previously blocked by a lack of rx dma buffers
	 * check if we now have enough to restart rx interrupt handling.
	 * NB: we know we are called at splvm which is above splnet.
	 */
	if (sc->sc_rxblocked && sc->sc_nrxfree > mwl_rxdmalow) {
		sc->sc_rxblocked = 0;
		mwl_hal_intrset(sc->sc_mh, sc->sc_imask);
	}
}