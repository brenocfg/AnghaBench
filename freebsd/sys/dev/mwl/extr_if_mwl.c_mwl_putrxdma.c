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
struct mwl_softc {int /*<<< orphan*/  sc_nrxfree; int /*<<< orphan*/  sc_rxfree; } ;
struct mwl_jumbo {int dummy; } ;

/* Variables and functions */
 struct mwl_jumbo* MWL_JUMBO_DATA2BUF (void*) ; 
 int /*<<< orphan*/  MWL_RXFREE_LOCK (struct mwl_softc*) ; 
 int /*<<< orphan*/  MWL_RXFREE_UNLOCK (struct mwl_softc*) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct mwl_jumbo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static __inline void
mwl_putrxdma(struct mwl_softc *sc, void *data)
{
	struct mwl_jumbo *buf;

	/* XXX bounds check data */
	MWL_RXFREE_LOCK(sc);
	buf = MWL_JUMBO_DATA2BUF(data);
	SLIST_INSERT_HEAD(&sc->sc_rxfree, buf, next);
	sc->sc_nrxfree++;
	MWL_RXFREE_UNLOCK(sc);
}