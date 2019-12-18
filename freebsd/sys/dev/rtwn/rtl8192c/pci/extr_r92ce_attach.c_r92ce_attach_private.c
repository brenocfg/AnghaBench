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
struct rtwn_softc {struct r92c_softc* sc_priv; int /*<<< orphan*/  sc_mtx; } ;
struct r92c_softc {int* rf_read_delay; int /*<<< orphan*/  rs_c2h_report; int /*<<< orphan*/  rs_c2h_timeout; int /*<<< orphan*/  rs_set_rom_opts; int /*<<< orphan*/  rs_tx_setup_macid; int /*<<< orphan*/  rs_tx_setup_hwseq; int /*<<< orphan*/  rs_tx_enable_ampdu; int /*<<< orphan*/  rs_set_gain; int /*<<< orphan*/  rs_get_txpower; int /*<<< orphan*/  rs_set_bw20; int /*<<< orphan*/ * rs_txpwr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_RTWN_PRIV ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 struct r92c_softc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r92c_get_txpower ; 
 int /*<<< orphan*/  r92c_set_bw20 ; 
 int /*<<< orphan*/  r92c_set_gain ; 
 int /*<<< orphan*/  r92c_tx_enable_ampdu ; 
 int /*<<< orphan*/  r92c_tx_setup_hwseq ; 
 int /*<<< orphan*/  r92c_tx_setup_macid ; 
 int /*<<< orphan*/  r92c_txpwr ; 
 int /*<<< orphan*/  r92ce_set_name ; 

__attribute__((used)) static void
r92ce_attach_private(struct rtwn_softc *sc)
{
	struct r92c_softc *rs;

	rs = malloc(sizeof(struct r92c_softc), M_RTWN_PRIV, M_WAITOK | M_ZERO);

	rs->rs_txpwr			= &r92c_txpwr;

	rs->rs_set_bw20			= r92c_set_bw20;
	rs->rs_get_txpower		= r92c_get_txpower;
	rs->rs_set_gain			= r92c_set_gain;
	rs->rs_tx_enable_ampdu		= r92c_tx_enable_ampdu;
	rs->rs_tx_setup_hwseq		= r92c_tx_setup_hwseq;
	rs->rs_tx_setup_macid		= r92c_tx_setup_macid;
	rs->rs_set_rom_opts		= r92ce_set_name;

	/* XXX TODO: test with net80211 ratectl! */
#ifndef RTWN_WITHOUT_UCODE
	rs->rs_c2h_timeout		= hz;

	callout_init_mtx(&rs->rs_c2h_report, &sc->sc_mtx, 0);
#endif

	rs->rf_read_delay[0]		= 1000;
	rs->rf_read_delay[1]		= 1000;
	rs->rf_read_delay[2]		= 1000;

	sc->sc_priv = rs;
}