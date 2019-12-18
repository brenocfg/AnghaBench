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
typedef  int /*<<< orphan*/  uint32_t ;
struct iwm_vap {scalar_t__ is_uploaded; int /*<<< orphan*/ * phy_ctxt; } ;
struct ieee80211com {int /*<<< orphan*/  ic_vaps; } ;
struct iwm_softc {TYPE_1__* cfg; int /*<<< orphan*/ * txq; int /*<<< orphan*/  rxq; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_flags; scalar_t__ sc_firmware_state; struct ieee80211com sc_ic; } ;
struct ieee80211vap {int dummy; } ;
struct TYPE_2__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  IWM_APMG_CLK_DIS_REG ; 
 int /*<<< orphan*/  IWM_APMG_CLK_VAL_DMA_CLK_RQT ; 
 int /*<<< orphan*/  IWM_CLRBITS (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_CSR_GP_CNTRL ; 
 int /*<<< orphan*/  IWM_CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ ; 
 int /*<<< orphan*/  IWM_CSR_RESET ; 
 int /*<<< orphan*/  IWM_CSR_RESET_REG_FLAG_SW_RESET ; 
 scalar_t__ IWM_DEVICE_FAMILY_7000 ; 
 int IWM_FH_TCSR_CHNL_NUM ; 
 int /*<<< orphan*/  IWM_FH_TCSR_CHNL_TX_CONFIG_REG (int) ; 
 int /*<<< orphan*/  IWM_FH_TSSR_TX_STATUS_REG ; 
 int /*<<< orphan*/  IWM_FH_TSSR_TX_STATUS_REG_MSK_CHNL_IDLE (int) ; 
 int /*<<< orphan*/  IWM_FLAG_TE_ACTIVE ; 
 int /*<<< orphan*/  IWM_FLAG_USE_ICT ; 
 int /*<<< orphan*/  IWM_READ (struct iwm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_SCD_TXFACT ; 
 int /*<<< orphan*/  IWM_SETBITS (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwm_vap* IWM_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  IWM_WRITE (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwm_apm_stop (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_check_rfkill (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_disable_interrupts (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_enable_rfkill_int (struct iwm_softc*) ; 
 scalar_t__ iwm_nic_lock (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_nic_unlock (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_pcie_rx_stop (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_poll_bit (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwm_prepare_card_hw (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_reset_rx_ring (struct iwm_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwm_reset_tx_ring (struct iwm_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwm_write_prph (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nitems (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iwm_stop_device(struct iwm_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);
	int chnl, qid;
	uint32_t mask = 0;

	/* tell the device to stop sending interrupts */
	iwm_disable_interrupts(sc);

	/*
	 * FreeBSD-local: mark the first vap as not-uploaded,
	 * so the next transition through auth/assoc
	 * will correctly populate the MAC context.
	 */
	if (vap) {
		struct iwm_vap *iv = IWM_VAP(vap);
		iv->phy_ctxt = NULL;
		iv->is_uploaded = 0;
	}
	sc->sc_firmware_state = 0;
	sc->sc_flags &= ~IWM_FLAG_TE_ACTIVE;

	/* device going down, Stop using ICT table */
	sc->sc_flags &= ~IWM_FLAG_USE_ICT;

	/* stop tx and rx.  tx and rx bits, as usual, are from if_iwn */

	if (iwm_nic_lock(sc)) {
		iwm_write_prph(sc, IWM_SCD_TXFACT, 0);

		/* Stop each Tx DMA channel */
		for (chnl = 0; chnl < IWM_FH_TCSR_CHNL_NUM; chnl++) {
			IWM_WRITE(sc,
			    IWM_FH_TCSR_CHNL_TX_CONFIG_REG(chnl), 0);
			mask |= IWM_FH_TSSR_TX_STATUS_REG_MSK_CHNL_IDLE(chnl);
		}

		/* Wait for DMA channels to be idle */
		if (!iwm_poll_bit(sc, IWM_FH_TSSR_TX_STATUS_REG, mask, mask,
		    5000)) {
			device_printf(sc->sc_dev,
			    "Failing on timeout while stopping DMA channel: [0x%08x]\n",
			    IWM_READ(sc, IWM_FH_TSSR_TX_STATUS_REG));
		}
		iwm_nic_unlock(sc);
	}
	iwm_pcie_rx_stop(sc);

	/* Stop RX ring. */
	iwm_reset_rx_ring(sc, &sc->rxq);

	/* Reset all TX rings. */
	for (qid = 0; qid < nitems(sc->txq); qid++)
		iwm_reset_tx_ring(sc, &sc->txq[qid]);

	if (sc->cfg->device_family == IWM_DEVICE_FAMILY_7000) {
		/* Power-down device's busmaster DMA clocks */
		if (iwm_nic_lock(sc)) {
			iwm_write_prph(sc, IWM_APMG_CLK_DIS_REG,
			    IWM_APMG_CLK_VAL_DMA_CLK_RQT);
			iwm_nic_unlock(sc);
		}
		DELAY(5);
	}

	/* Make sure (redundant) we've released our request to stay awake */
	IWM_CLRBITS(sc, IWM_CSR_GP_CNTRL,
	    IWM_CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);

	/* Stop the device, and put it in low power state */
	iwm_apm_stop(sc);

	/* stop and reset the on-board processor */
	IWM_SETBITS(sc, IWM_CSR_RESET, IWM_CSR_RESET_REG_FLAG_SW_RESET);
	DELAY(5000);

	/*
	 * Upon stop, the APM issues an interrupt if HW RF kill is set.
	 */
	iwm_disable_interrupts(sc);

	/*
	 * Even if we stop the HW, we still want the RF kill
	 * interrupt
	 */
	iwm_enable_rfkill_int(sc);
	iwm_check_rfkill(sc);

	iwm_prepare_card_hw(sc);
}