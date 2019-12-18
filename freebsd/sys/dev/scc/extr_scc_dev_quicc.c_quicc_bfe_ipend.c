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
typedef  int uint16_t ;
struct scc_bas {int dummy; } ;
struct scc_softc {int /*<<< orphan*/  sc_hwmtx; struct scc_chan* sc_chan; struct scc_bas sc_bas; } ;
struct scc_chan {int ch_ipend; int /*<<< orphan*/  ch_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUICC_REG_SCC_SCCE (int) ; 
 int SER_INT_BREAK ; 
 int SER_INT_OVERRUN ; 
 int SER_INT_RXREADY ; 
 int SER_INT_TXIDLE ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int quicc_read2 (struct scc_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicc_write2 (struct scc_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
quicc_bfe_ipend(struct scc_softc *sc)
{
	struct scc_bas *bas;
	struct scc_chan *ch;
	int c, ipend;
	uint16_t scce;

	bas = &sc->sc_bas;
	ipend = 0;
	for (c = 0; c < 4; c++) {
		ch = &sc->sc_chan[c];
		if (!ch->ch_enabled)
			continue;
		ch->ch_ipend = 0;
		mtx_lock_spin(&sc->sc_hwmtx);
		scce = quicc_read2(bas, QUICC_REG_SCC_SCCE(c));
		quicc_write2(bas, QUICC_REG_SCC_SCCE(c), ~0);
		mtx_unlock_spin(&sc->sc_hwmtx);
		if (scce & 0x0001)
			ch->ch_ipend |= SER_INT_RXREADY;
		if (scce & 0x0002)
			ch->ch_ipend |= SER_INT_TXIDLE;
		if (scce & 0x0004)
			ch->ch_ipend |= SER_INT_OVERRUN;
		if (scce & 0x0020)
			ch->ch_ipend |= SER_INT_BREAK;
		/* XXX SIGNALS */
		ipend |= ch->ch_ipend;
	}
	return (ipend);
}