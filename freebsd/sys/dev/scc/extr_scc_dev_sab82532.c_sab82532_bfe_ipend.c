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
typedef  int uint8_t ;
struct scc_bas {int dummy; } ;
struct scc_softc {int /*<<< orphan*/  sc_hwmtx; struct scc_chan* sc_chan; struct scc_bas sc_bas; } ;
struct scc_chan {int ch_ipend; } ;

/* Variables and functions */
 int SAB_CHANLEN ; 
 scalar_t__ SAB_CMDR ; 
 int /*<<< orphan*/  SAB_CMDR_RFRD ; 
 scalar_t__ SAB_ISR0 ; 
 int SAB_ISR0_CDSC ; 
 int SAB_ISR0_RFO ; 
 int SAB_ISR0_RPF ; 
 int SAB_ISR0_TCD ; 
 int SAB_ISR0_TIME ; 
 scalar_t__ SAB_ISR1 ; 
 int SAB_ISR1_ALLS ; 
 int SAB_ISR1_BRKT ; 
 int SAB_ISR1_CSC ; 
 int SAB_NCHAN ; 
 scalar_t__ SAB_STAR ; 
 int SAB_STAR_CEC ; 
 int SER_INT_BREAK ; 
 int SER_INT_OVERRUN ; 
 int SER_INT_RXREADY ; 
 int SER_INT_SIGCHG ; 
 int SER_INT_TXIDLE ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scc_barrier (struct scc_bas*) ; 
 int scc_getreg (struct scc_bas*,scalar_t__) ; 
 int /*<<< orphan*/  scc_setreg (struct scc_bas*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sab82532_bfe_ipend(struct scc_softc *sc)
{
	struct scc_bas *bas;
	struct scc_chan *ch;
	int ipend;
	int c, ofs;
	uint8_t isr0, isr1;

	bas = &sc->sc_bas;
	ipend = 0;
	for (c = 0; c < SAB_NCHAN; c++) {
		ch = &sc->sc_chan[c];
		ofs = c * SAB_CHANLEN;
		mtx_lock_spin(&sc->sc_hwmtx);
		isr0 = scc_getreg(bas, ofs + SAB_ISR0);
		isr1 = scc_getreg(bas, ofs + SAB_ISR1);
		scc_barrier(bas);
		if (isr0 & SAB_ISR0_TIME) {
			while (scc_getreg(bas, ofs + SAB_STAR) & SAB_STAR_CEC)
				;
			scc_setreg(bas, ofs + SAB_CMDR, SAB_CMDR_RFRD);
			scc_barrier(bas);
		}
		mtx_unlock_spin(&sc->sc_hwmtx);

		ch->ch_ipend = 0;
		if (isr1 & SAB_ISR1_BRKT)
			ch->ch_ipend |= SER_INT_BREAK;
		if (isr0 & SAB_ISR0_RFO)
			ch->ch_ipend |= SER_INT_OVERRUN;
		if (isr0 & (SAB_ISR0_TCD|SAB_ISR0_RPF))
			ch->ch_ipend |= SER_INT_RXREADY;
		if ((isr0 & SAB_ISR0_CDSC) || (isr1 & SAB_ISR1_CSC))
			ch->ch_ipend |= SER_INT_SIGCHG;
		if (isr1 & SAB_ISR1_ALLS)
			ch->ch_ipend |= SER_INT_TXIDLE;
		ipend |= ch->ch_ipend;
	}
	return (ipend);
}