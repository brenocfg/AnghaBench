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
struct ieee80211com {int /*<<< orphan*/  ic_scan_end; int /*<<< orphan*/  ic_scan_start; } ;
struct rtwn_softc {char* fwname; int fwsig; void* agc_size; int /*<<< orphan*/ * agc_prog; struct ieee80211com sc_ic; struct r92c_softc* sc_priv; } ;
struct r92c_softc {int chip; scalar_t__ board_type; int /*<<< orphan*/  rs_scan_end; int /*<<< orphan*/  rs_scan_start; int /*<<< orphan*/ * rs_txagc; } ;

/* Variables and functions */
 scalar_t__ R92C_BOARD_TYPE_HIGHPA ; 
 int R92C_CHIP_92C ; 
 int R92C_CHIP_UMC_A_CUT ; 
 void* nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r92c_scan_end ; 
 int /*<<< orphan*/  r92c_scan_start ; 
 int /*<<< orphan*/ * rtl8188ru_agc ; 
 int /*<<< orphan*/ * rtl8188ru_txagc ; 
 int /*<<< orphan*/ * rtl8192ce_agc ; 
 int /*<<< orphan*/ * rtl8192cu_txagc ; 

__attribute__((used)) static void
r92cu_postattach(struct rtwn_softc *sc)
{
	struct r92c_softc *rs = sc->sc_priv;
	struct ieee80211com *ic = &sc->sc_ic;

	if (!(rs->chip & R92C_CHIP_92C) &&
	    rs->board_type == R92C_BOARD_TYPE_HIGHPA) {
		sc->agc_prog = &rtl8188ru_agc[0];
		sc->agc_size = nitems(rtl8188ru_agc);
		rs->rs_txagc = &rtl8188ru_txagc[0];
	} else {
		sc->agc_prog = &rtl8192ce_agc[0];
		sc->agc_size = nitems(rtl8192ce_agc);
		rs->rs_txagc = &rtl8192cu_txagc[0];
	}

	if ((rs->chip & (R92C_CHIP_UMC_A_CUT | R92C_CHIP_92C)) ==
		    R92C_CHIP_UMC_A_CUT) {
		sc->fwname = "rtwn-rtl8192cfwU";
	} else {
		sc->fwname = "rtwn-rtl8192cfwT";
	}
	sc->fwsig = 0x88c;

	rs->rs_scan_start = ic->ic_scan_start;
	ic->ic_scan_start = r92c_scan_start;
	rs->rs_scan_end = ic->ic_scan_end;
	ic->ic_scan_end = r92c_scan_end;
}