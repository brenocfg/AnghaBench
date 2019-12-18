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
struct rtwn_softc {scalar_t__ sc_ratectl_sysctl; scalar_t__ sc_ratectl; } ;

/* Variables and functions */
 scalar_t__ R88E_MACID_NO_LINK ; 
 int /*<<< orphan*/  R88E_TX_RPT1_ENA ; 
 int /*<<< orphan*/  R88E_TX_RPT_CTRL ; 
 scalar_t__ R92C_PCIE_CTRL_REG ; 
 int /*<<< orphan*/  RTWN_MACID_BC ; 
 scalar_t__ RTWN_RATECTL_FW ; 
 scalar_t__ RTWN_RATECTL_NET80211 ; 
 int /*<<< orphan*/  r88e_iq_calib (struct rtwn_softc*) ; 
 int /*<<< orphan*/  r88e_macid_enable_link (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r92c_lc_calib (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_write_4 (struct rtwn_softc*,scalar_t__,int) ; 

void
r88ee_post_init(struct rtwn_softc *sc)
{

	/* Enable per-packet TX report. */
	rtwn_setbits_1(sc, R88E_TX_RPT_CTRL, 0, R88E_TX_RPT1_ENA);

	/* Disable Tx if MACID is not associated. */
	rtwn_write_4(sc, R88E_MACID_NO_LINK, 0xffffffff);
	rtwn_write_4(sc, R88E_MACID_NO_LINK + 4, 0xffffffff);
	r88e_macid_enable_link(sc, RTWN_MACID_BC, 1);

	/* Perform LO and IQ calibrations. */
	r88e_iq_calib(sc);
	/* Perform LC calibration. */
	r92c_lc_calib(sc);

	/* Enable Rx DMA */
	rtwn_write_1(sc, R92C_PCIE_CTRL_REG + 1, 0);

	if (sc->sc_ratectl_sysctl == RTWN_RATECTL_FW) {
		/* No support (yet?) for f/w rate adaptation. */
		sc->sc_ratectl = RTWN_RATECTL_NET80211;
	} else
		sc->sc_ratectl = sc->sc_ratectl_sysctl;
}