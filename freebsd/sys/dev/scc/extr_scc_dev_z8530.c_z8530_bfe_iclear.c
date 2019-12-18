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
struct scc_bas {int dummy; } ;
struct scc_softc {int /*<<< orphan*/  sc_hwmtx; struct scc_bas sc_bas; } ;
struct scc_chan {int ch_nr; int ch_ipend; } ;

/* Variables and functions */
 int CHAN_A ; 
 int CHAN_B ; 
 int /*<<< orphan*/  CR_RSTERR ; 
 int /*<<< orphan*/  CR_RSTTXI ; 
 scalar_t__ REG_CTRL ; 
 scalar_t__ REG_DATA ; 
 int SER_INT_BREAK ; 
 int SER_INT_OVERRUN ; 
 int SER_INT_RXREADY ; 
 int SER_INT_TXIDLE ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scc_barrier (struct scc_bas*) ; 
 int /*<<< orphan*/  scc_getreg (struct scc_bas*,scalar_t__) ; 
 int /*<<< orphan*/  scc_setreg (struct scc_bas*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
z8530_bfe_iclear(struct scc_softc *sc, struct scc_chan *ch)
{
	struct scc_bas *bas;
	int c;

	bas = &sc->sc_bas;
	c = (ch->ch_nr == 1) ? CHAN_A : CHAN_B;
	mtx_lock_spin(&sc->sc_hwmtx);
	if (ch->ch_ipend & SER_INT_TXIDLE) {
		scc_setreg(bas, c + REG_CTRL, CR_RSTTXI);
		scc_barrier(bas);
	}
	if (ch->ch_ipend & SER_INT_RXREADY) {
		scc_getreg(bas, c + REG_DATA);
		scc_barrier(bas);
	}
	if (ch->ch_ipend & (SER_INT_OVERRUN|SER_INT_BREAK))
		scc_setreg(bas, c + REG_CTRL, CR_RSTERR);
	mtx_unlock_spin(&sc->sc_hwmtx);
	return (0);
}