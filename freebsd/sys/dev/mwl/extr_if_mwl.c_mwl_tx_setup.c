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
struct mwl_txq {int dummy; } ;
struct mwl_softc {struct mwl_txq** sc_ac2q; struct mwl_txq* sc_txq; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int MWL_NUM_TX_QUEUES ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  mwl_txq_init (struct mwl_softc*,struct mwl_txq*,int) ; 
 int nitems (struct mwl_txq**) ; 

__attribute__((used)) static int
mwl_tx_setup(struct mwl_softc *sc, int ac, int mvtype)
{
	struct mwl_txq *txq;

	if (ac >= nitems(sc->sc_ac2q)) {
		device_printf(sc->sc_dev, "AC %u out of range, max %zu!\n",
			ac, nitems(sc->sc_ac2q));
		return 0;
	}
	if (mvtype >= MWL_NUM_TX_QUEUES) {
		device_printf(sc->sc_dev, "mvtype %u out of range, max %u!\n",
			mvtype, MWL_NUM_TX_QUEUES);
		return 0;
	}
	txq = &sc->sc_txq[mvtype];
	mwl_txq_init(sc, txq, mvtype);
	sc->sc_ac2q[ac] = txq;
	return 1;
}