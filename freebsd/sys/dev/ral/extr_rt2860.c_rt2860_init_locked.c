#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int paddr; } ;
struct ieee80211com {int /*<<< orphan*/  ic_curchan; int /*<<< orphan*/  ic_macaddr; int /*<<< orphan*/  ic_vaps; } ;
struct rt2860_softc {int* txpow20mhz; int mac_ver; int sc_flags; scalar_t__ rf_rev; int* led; int nrxchains; int ntxchains; int pslevel; int /*<<< orphan*/  watchdog_ch; TYPE_3__* bbp; int /*<<< orphan*/  sc_dev; TYPE_2__ rxq; TYPE_1__* txq; scalar_t__ rfswitch; struct ieee80211com sc_ic; } ;
struct rt2860_rxwi {int dummy; } ;
struct ieee80211vap {int /*<<< orphan*/  iv_myaddr; } ;
struct TYPE_9__ {int val; int /*<<< orphan*/  reg; } ;
struct TYPE_8__ {int reg; int val; } ;
struct TYPE_6__ {int paddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int IEEE80211_RTS_DEFAULT ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  RAL_BARRIER_WRITE (struct rt2860_softc*) ; 
 int /*<<< orphan*/  RAL_LOCK_ASSERT (struct rt2860_softc*) ; 
 int RAL_READ (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_SET_REGION_4 (struct rt2860_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int /*<<< orphan*/ ,int) ; 
 int RT2860_ADVANCED_PS ; 
 int RT2860_BBP_HRST ; 
 int /*<<< orphan*/  RT2860_DELAY_INT_CFG ; 
 int RT2860_DLY_PAPE_EN_SHIFT ; 
 int /*<<< orphan*/  RT2860_GPIO_CTRL ; 
 int /*<<< orphan*/  RT2860_H2M_BBPAGENT ; 
 int /*<<< orphan*/  RT2860_H2M_MAILBOX ; 
 int /*<<< orphan*/  RT2860_INT_MASK ; 
 int /*<<< orphan*/  RT2860_INT_STATUS ; 
 int RT2860_IO_RA_PE ; 
 int RT2860_IO_RF_PE ; 
 int /*<<< orphan*/  RT2860_IVEIV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT2860_LED_RADIO ; 
 int RT2860_MAC_SRST ; 
 int /*<<< orphan*/  RT2860_MAC_STATUS_REG ; 
 int /*<<< orphan*/  RT2860_MAC_SYS_CTRL ; 
 int /*<<< orphan*/  RT2860_MAX_LEN_CFG ; 
 int /*<<< orphan*/  RT2860_MCU_CMD_LED1 ; 
 int /*<<< orphan*/  RT2860_MCU_CMD_LED2 ; 
 int /*<<< orphan*/  RT2860_MCU_CMD_LED3 ; 
 int /*<<< orphan*/  RT2860_MCU_CMD_PSLEVEL ; 
 int /*<<< orphan*/  RT2860_MCU_CMD_RFRESET ; 
 int /*<<< orphan*/  RT2860_MCU_CMD_SLEEP ; 
 int /*<<< orphan*/  RT2860_MCU_CMD_WAKEUP ; 
 int RT2860_PCIE ; 
 int /*<<< orphan*/  RT2860_PCI_CFG ; 
 int RT2860_PCI_CFG_PCI ; 
 int /*<<< orphan*/  RT2860_PKEY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT2860_PWR_PIN_CFG ; 
 int RT2860_RST_DRX_IDX0 ; 
 int RT2860_RST_DTX_IDX0 ; 
 int RT2860_RST_DTX_IDX1 ; 
 int RT2860_RST_DTX_IDX2 ; 
 int RT2860_RST_DTX_IDX3 ; 
 int RT2860_RST_DTX_IDX4 ; 
 int RT2860_RST_DTX_IDX5 ; 
 int RT2860_RUNNING ; 
 int /*<<< orphan*/  RT2860_RX_BASE_PTR ; 
 int /*<<< orphan*/  RT2860_RX_CALC_IDX ; 
 int RT2860_RX_DMA_BUSY ; 
 int RT2860_RX_DMA_EN ; 
 int /*<<< orphan*/  RT2860_RX_MAX_CNT ; 
 int RT2860_RX_RING_COUNT ; 
 int RT2860_RX_STATUS_BUSY ; 
 int /*<<< orphan*/  RT2860_SKEY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT2860_SKEY_MODE_0_7 ; 
 int /*<<< orphan*/  RT2860_SYS_CTRL ; 
 int /*<<< orphan*/  RT2860_TX_BASE_PTR (int) ; 
 int /*<<< orphan*/  RT2860_TX_CTX_IDX (int) ; 
 int RT2860_TX_DMA_BUSY ; 
 int RT2860_TX_DMA_EN ; 
 int /*<<< orphan*/  RT2860_TX_MAX_CNT (int) ; 
 int /*<<< orphan*/  RT2860_TX_PWR_CFG (int) ; 
 int RT2860_TX_RING_COUNT ; 
 int /*<<< orphan*/  RT2860_TX_RTS_CFG ; 
 int RT2860_TX_STATUS_BUSY ; 
 int /*<<< orphan*/  RT2860_TX_SW_CFG0 ; 
 int RT2860_TX_WB_DDONE ; 
 int /*<<< orphan*/  RT2860_US_CYC_CNT ; 
 int /*<<< orphan*/  RT2860_WCID_ATTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT2860_WCID_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT2860_WPDMA_GLO_CFG ; 
 int /*<<< orphan*/  RT2860_WPDMA_RST_IDX ; 
 scalar_t__ RT3070_RF_2020 ; 
 scalar_t__ RT3070_RF_3020 ; 
 scalar_t__ RT3070_RF_3320 ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rt2860_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int nitems (TYPE_4__*) ; 
 int rt2860_bbp_init (struct rt2860_softc*) ; 
 TYPE_4__* rt2860_def_mac ; 
 int rt2860_load_microcode (struct rt2860_softc*) ; 
 int rt2860_mcu_bbp_read (struct rt2860_softc*,int) ; 
 int /*<<< orphan*/  rt2860_mcu_bbp_write (struct rt2860_softc*,int,int) ; 
 int /*<<< orphan*/  rt2860_mcu_cmd (struct rt2860_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rt2860_set_leds (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2860_set_macaddr (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2860_stop_locked (struct rt2860_softc*) ; 
 int /*<<< orphan*/  rt2860_switch_chan (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int rt2860_txrx_enable (struct rt2860_softc*) ; 
 int /*<<< orphan*/  rt2860_updateprot (struct rt2860_softc*) ; 
 int /*<<< orphan*/  rt2860_watchdog ; 
 int rt3090_rf_init (struct rt2860_softc*) ; 
 int /*<<< orphan*/  rt3090_rf_setup (struct rt2860_softc*) ; 
 int /*<<< orphan*/  rt3090_rf_wakeup (struct rt2860_softc*) ; 
 int /*<<< orphan*/  rt3090_set_rx_antenna (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt5390_rf_init (struct rt2860_softc*) ; 
 int /*<<< orphan*/  rt5390_rf_wakeup (struct rt2860_softc*) ; 

__attribute__((used)) static void
rt2860_init_locked(struct rt2860_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);
	uint32_t tmp;
	uint8_t bbp1, bbp3;
	int i, qid, ridx, ntries, error;

	RAL_LOCK_ASSERT(sc);

	if (sc->rfswitch) {
		/* hardware has a radio switch on GPIO pin 2 */
		if (!(RAL_READ(sc, RT2860_GPIO_CTRL) & (1 << 2))) {
			device_printf(sc->sc_dev,
			    "radio is disabled by hardware switch\n");
#ifdef notyet
			rt2860_stop_locked(sc);
			return;
#endif
		}
	}
	RAL_WRITE(sc, RT2860_PWR_PIN_CFG, RT2860_IO_RA_PE);

	/* disable DMA */
	tmp = RAL_READ(sc, RT2860_WPDMA_GLO_CFG);
	tmp &= ~(RT2860_RX_DMA_BUSY | RT2860_RX_DMA_EN | RT2860_TX_DMA_BUSY |
	    RT2860_TX_DMA_EN);
	tmp |= RT2860_TX_WB_DDONE;
	RAL_WRITE(sc, RT2860_WPDMA_GLO_CFG, tmp);

	/* reset DMA indexes */
	RAL_WRITE(sc, RT2860_WPDMA_RST_IDX, RT2860_RST_DRX_IDX0 |
	    RT2860_RST_DTX_IDX5 | RT2860_RST_DTX_IDX4 | RT2860_RST_DTX_IDX3 |
	    RT2860_RST_DTX_IDX2 | RT2860_RST_DTX_IDX1 | RT2860_RST_DTX_IDX0);

	/* PBF hardware reset */
	RAL_WRITE(sc, RT2860_SYS_CTRL, 0xe1f);
	RAL_BARRIER_WRITE(sc);
	RAL_WRITE(sc, RT2860_SYS_CTRL, 0xe00);

	if ((error = rt2860_load_microcode(sc)) != 0) {
		device_printf(sc->sc_dev, "could not load 8051 microcode\n");
		rt2860_stop_locked(sc);
		return;
	}

	rt2860_set_macaddr(sc, vap ? vap->iv_myaddr : ic->ic_macaddr);

	/* init Tx power for all Tx rates (from EEPROM) */
	for (ridx = 0; ridx < 5; ridx++) {
		if (sc->txpow20mhz[ridx] == 0xffffffff)
			continue;
		RAL_WRITE(sc, RT2860_TX_PWR_CFG(ridx), sc->txpow20mhz[ridx]);
	}

	for (ntries = 0; ntries < 100; ntries++) {
		tmp = RAL_READ(sc, RT2860_WPDMA_GLO_CFG);
		if ((tmp & (RT2860_TX_DMA_BUSY | RT2860_RX_DMA_BUSY)) == 0)
			break;
		DELAY(1000);
	}
	if (ntries == 100) {
		device_printf(sc->sc_dev, "timeout waiting for DMA engine\n");
		rt2860_stop_locked(sc);
		return;
	}
	tmp &= ~(RT2860_RX_DMA_BUSY | RT2860_RX_DMA_EN | RT2860_TX_DMA_BUSY |
	    RT2860_TX_DMA_EN);
	tmp |= RT2860_TX_WB_DDONE;
	RAL_WRITE(sc, RT2860_WPDMA_GLO_CFG, tmp);

	/* reset Rx ring and all 6 Tx rings */
	RAL_WRITE(sc, RT2860_WPDMA_RST_IDX, 0x1003f);

	/* PBF hardware reset */
	RAL_WRITE(sc, RT2860_SYS_CTRL, 0xe1f);
	RAL_BARRIER_WRITE(sc);
	RAL_WRITE(sc, RT2860_SYS_CTRL, 0xe00);

	RAL_WRITE(sc, RT2860_PWR_PIN_CFG, RT2860_IO_RA_PE | RT2860_IO_RF_PE);

	RAL_WRITE(sc, RT2860_MAC_SYS_CTRL, RT2860_BBP_HRST | RT2860_MAC_SRST);
	RAL_BARRIER_WRITE(sc);
	RAL_WRITE(sc, RT2860_MAC_SYS_CTRL, 0);

	for (i = 0; i < nitems(rt2860_def_mac); i++)
		RAL_WRITE(sc, rt2860_def_mac[i].reg, rt2860_def_mac[i].val);
	if (sc->mac_ver >= 0x5390)
		RAL_WRITE(sc, RT2860_TX_SW_CFG0, 0x00000404);
	else if (sc->mac_ver >= 0x3071) {
		/* set delay of PA_PE assertion to 1us (unit of 0.25us) */
		RAL_WRITE(sc, RT2860_TX_SW_CFG0,
		    4 << RT2860_DLY_PAPE_EN_SHIFT);
	}

	if (!(RAL_READ(sc, RT2860_PCI_CFG) & RT2860_PCI_CFG_PCI)) {
		sc->sc_flags |= RT2860_PCIE;
		/* PCIe has different clock cycle count than PCI */
		tmp = RAL_READ(sc, RT2860_US_CYC_CNT);
		tmp = (tmp & ~0xff) | 0x7d;
		RAL_WRITE(sc, RT2860_US_CYC_CNT, tmp);
	}

	/* wait while MAC is busy */
	for (ntries = 0; ntries < 100; ntries++) {
		if (!(RAL_READ(sc, RT2860_MAC_STATUS_REG) &
		    (RT2860_RX_STATUS_BUSY | RT2860_TX_STATUS_BUSY)))
			break;
		DELAY(1000);
	}
	if (ntries == 100) {
		device_printf(sc->sc_dev, "timeout waiting for MAC\n");
		rt2860_stop_locked(sc);
		return;
	}

	/* clear Host to MCU mailbox */
	RAL_WRITE(sc, RT2860_H2M_BBPAGENT, 0);
	RAL_WRITE(sc, RT2860_H2M_MAILBOX, 0);

	rt2860_mcu_cmd(sc, RT2860_MCU_CMD_RFRESET, 0, 0);
	DELAY(1000);

	if ((error = rt2860_bbp_init(sc)) != 0) {
		rt2860_stop_locked(sc);
		return;
	}

	/* clear RX WCID search table */
	RAL_SET_REGION_4(sc, RT2860_WCID_ENTRY(0), 0, 512);
	/* clear pairwise key table */
	RAL_SET_REGION_4(sc, RT2860_PKEY(0), 0, 2048);
	/* clear IV/EIV table */
	RAL_SET_REGION_4(sc, RT2860_IVEIV(0), 0, 512);
	/* clear WCID attribute table */
	RAL_SET_REGION_4(sc, RT2860_WCID_ATTR(0), 0, 256);
	/* clear shared key table */
	RAL_SET_REGION_4(sc, RT2860_SKEY(0, 0), 0, 8 * 32);
	/* clear shared key mode */
	RAL_SET_REGION_4(sc, RT2860_SKEY_MODE_0_7, 0, 4);

	/* init Tx rings (4 EDCAs + HCCA + Mgt) */
	for (qid = 0; qid < 6; qid++) {
		RAL_WRITE(sc, RT2860_TX_BASE_PTR(qid), sc->txq[qid].paddr);
		RAL_WRITE(sc, RT2860_TX_MAX_CNT(qid), RT2860_TX_RING_COUNT);
		RAL_WRITE(sc, RT2860_TX_CTX_IDX(qid), 0);
	}

	/* init Rx ring */
	RAL_WRITE(sc, RT2860_RX_BASE_PTR, sc->rxq.paddr);
	RAL_WRITE(sc, RT2860_RX_MAX_CNT, RT2860_RX_RING_COUNT);
	RAL_WRITE(sc, RT2860_RX_CALC_IDX, RT2860_RX_RING_COUNT - 1);

	/* setup maximum buffer sizes */
	RAL_WRITE(sc, RT2860_MAX_LEN_CFG, 1 << 12 |
	    (MCLBYTES - sizeof (struct rt2860_rxwi) - 2));

	for (ntries = 0; ntries < 100; ntries++) {
		tmp = RAL_READ(sc, RT2860_WPDMA_GLO_CFG);
		if ((tmp & (RT2860_TX_DMA_BUSY | RT2860_RX_DMA_BUSY)) == 0)
			break;
		DELAY(1000);
	}
	if (ntries == 100) {
		device_printf(sc->sc_dev, "timeout waiting for DMA engine\n");
		rt2860_stop_locked(sc);
		return;
	}
	tmp &= ~(RT2860_RX_DMA_BUSY | RT2860_RX_DMA_EN | RT2860_TX_DMA_BUSY |
	    RT2860_TX_DMA_EN);
	tmp |= RT2860_TX_WB_DDONE;
	RAL_WRITE(sc, RT2860_WPDMA_GLO_CFG, tmp);

	/* disable interrupts mitigation */
	RAL_WRITE(sc, RT2860_DELAY_INT_CFG, 0);

	/* write vendor-specific BBP values (from EEPROM) */
	for (i = 0; i < 8; i++) {
		if (sc->bbp[i].reg == 0 || sc->bbp[i].reg == 0xff)
			continue;
		rt2860_mcu_bbp_write(sc, sc->bbp[i].reg, sc->bbp[i].val);
	}

	/* select Main antenna for 1T1R devices */
	if (sc->rf_rev == RT3070_RF_2020 ||
	    sc->rf_rev == RT3070_RF_3020 ||
	    sc->rf_rev == RT3070_RF_3320 ||
	    sc->mac_ver == 0x5390)
		rt3090_set_rx_antenna(sc, 0);

	/* send LEDs operating mode to microcontroller */
	rt2860_mcu_cmd(sc, RT2860_MCU_CMD_LED1, sc->led[0], 0);
	rt2860_mcu_cmd(sc, RT2860_MCU_CMD_LED2, sc->led[1], 0);
	rt2860_mcu_cmd(sc, RT2860_MCU_CMD_LED3, sc->led[2], 0);

	if (sc->mac_ver >= 0x5390)
		rt5390_rf_init(sc);
	else if (sc->mac_ver >= 0x3071) {
		if ((error = rt3090_rf_init(sc)) != 0) {
			rt2860_stop_locked(sc);
			return;
		}
	}

	rt2860_mcu_cmd(sc, RT2860_MCU_CMD_SLEEP, 0x02ff, 1);
	rt2860_mcu_cmd(sc, RT2860_MCU_CMD_WAKEUP, 0, 1);

	if (sc->mac_ver >= 0x5390)
		rt5390_rf_wakeup(sc);
	else if (sc->mac_ver >= 0x3071)
		rt3090_rf_wakeup(sc);

	/* disable non-existing Rx chains */
	bbp3 = rt2860_mcu_bbp_read(sc, 3);
	bbp3 &= ~(1 << 3 | 1 << 4);
	if (sc->nrxchains == 2)
		bbp3 |= 1 << 3;
	else if (sc->nrxchains == 3)
		bbp3 |= 1 << 4;
	rt2860_mcu_bbp_write(sc, 3, bbp3);

	/* disable non-existing Tx chains */
	bbp1 = rt2860_mcu_bbp_read(sc, 1);
	if (sc->ntxchains == 1)
		bbp1 = (bbp1 & ~(1 << 3 | 1 << 4));
	else if (sc->mac_ver == 0x3593 && sc->ntxchains == 2)
		bbp1 = (bbp1 & ~(1 << 4)) | 1 << 3;
	else if (sc->mac_ver == 0x3593 && sc->ntxchains == 3)
		bbp1 = (bbp1 & ~(1 << 3)) | 1 << 4;
	rt2860_mcu_bbp_write(sc, 1, bbp1);

	if (sc->mac_ver >= 0x3071)
		rt3090_rf_setup(sc);

	/* select default channel */
	rt2860_switch_chan(sc, ic->ic_curchan);

	/* reset RF from MCU */
	rt2860_mcu_cmd(sc, RT2860_MCU_CMD_RFRESET, 0, 0);

	/* set RTS threshold */
	tmp = RAL_READ(sc, RT2860_TX_RTS_CFG);
	tmp &= ~0xffff00;
	tmp |= IEEE80211_RTS_DEFAULT << 8;
	RAL_WRITE(sc, RT2860_TX_RTS_CFG, tmp);

	/* setup initial protection mode */
	rt2860_updateprot(sc);

	/* turn radio LED on */
	rt2860_set_leds(sc, RT2860_LED_RADIO);

	/* enable Tx/Rx DMA engine */
	if ((error = rt2860_txrx_enable(sc)) != 0) {
		rt2860_stop_locked(sc);
		return;
	}

	/* clear pending interrupts */
	RAL_WRITE(sc, RT2860_INT_STATUS, 0xffffffff);
	/* enable interrupts */
	RAL_WRITE(sc, RT2860_INT_MASK, 0x3fffc);

	if (sc->sc_flags & RT2860_ADVANCED_PS)
		rt2860_mcu_cmd(sc, RT2860_MCU_CMD_PSLEVEL, sc->pslevel, 0);

	sc->sc_flags |= RT2860_RUNNING;

	callout_reset(&sc->watchdog_ch, hz, rt2860_watchdog, sc);
}