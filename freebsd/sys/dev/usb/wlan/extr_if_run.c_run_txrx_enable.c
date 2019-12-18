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
typedef  int uint32_t ;
struct ieee80211com {scalar_t__ ic_opmode; } ;
struct run_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ IEEE80211_M_MONITOR ; 
 scalar_t__ IEEE80211_M_STA ; 
 int RT2860_DROP_ACK ; 
 int RT2860_DROP_BA ; 
 int RT2860_DROP_CFACK ; 
 int RT2860_DROP_CFEND ; 
 int RT2860_DROP_CRC_ERR ; 
 int RT2860_DROP_CTRL_RSV ; 
 int RT2860_DROP_CTS ; 
 int RT2860_DROP_DUPL ; 
 int RT2860_DROP_PHY_ERR ; 
 int RT2860_DROP_PSPOLL ; 
 int RT2860_DROP_RTS ; 
 int RT2860_DROP_UC_NOME ; 
 int RT2860_DROP_VER_ERR ; 
 int RT2860_MAC_RX_EN ; 
 int /*<<< orphan*/  RT2860_MAC_SYS_CTRL ; 
 int RT2860_MAC_TX_EN ; 
 int RT2860_RX_DMA_BUSY ; 
 int RT2860_RX_DMA_EN ; 
 int /*<<< orphan*/  RT2860_RX_FILTR_CFG ; 
 int RT2860_TX_DMA_BUSY ; 
 int RT2860_TX_DMA_EN ; 
 int RT2860_TX_WB_DDONE ; 
 int /*<<< orphan*/  RT2860_USB_DMA_CFG ; 
 int RT2860_USB_RX_AGG_EN ; 
 int RT2860_USB_RX_AGG_LMT (int) ; 
 int RT2860_USB_RX_AGG_TO (int) ; 
 int RT2860_USB_RX_EN ; 
 int RT2860_USB_TX_EN ; 
 int /*<<< orphan*/  RT2860_WPDMA_GLO_CFG ; 
 int /*<<< orphan*/  run_delay (struct run_softc*,int) ; 
 int run_read (struct run_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  run_write (struct run_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
run_txrx_enable(struct run_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t tmp;
	int error, ntries;

	run_write(sc, RT2860_MAC_SYS_CTRL, RT2860_MAC_TX_EN);
	for (ntries = 0; ntries < 200; ntries++) {
		if ((error = run_read(sc, RT2860_WPDMA_GLO_CFG, &tmp)) != 0)
			return (error);
		if ((tmp & (RT2860_TX_DMA_BUSY | RT2860_RX_DMA_BUSY)) == 0)
			break;
		run_delay(sc, 50);
	}
	if (ntries == 200)
		return (ETIMEDOUT);

	run_delay(sc, 50);

	tmp |= RT2860_RX_DMA_EN | RT2860_TX_DMA_EN | RT2860_TX_WB_DDONE;
	run_write(sc, RT2860_WPDMA_GLO_CFG, tmp);

	/* enable Rx bulk aggregation (set timeout and limit) */
	tmp = RT2860_USB_TX_EN | RT2860_USB_RX_EN | RT2860_USB_RX_AGG_EN |
	    RT2860_USB_RX_AGG_TO(128) | RT2860_USB_RX_AGG_LMT(2);
	run_write(sc, RT2860_USB_DMA_CFG, tmp);

	/* set Rx filter */
	tmp = RT2860_DROP_CRC_ERR | RT2860_DROP_PHY_ERR;
	if (ic->ic_opmode != IEEE80211_M_MONITOR) {
		tmp |= RT2860_DROP_UC_NOME | RT2860_DROP_DUPL |
		    RT2860_DROP_CTS | RT2860_DROP_BA | RT2860_DROP_ACK |
		    RT2860_DROP_VER_ERR | RT2860_DROP_CTRL_RSV |
		    RT2860_DROP_CFACK | RT2860_DROP_CFEND;
		if (ic->ic_opmode == IEEE80211_M_STA)
			tmp |= RT2860_DROP_RTS | RT2860_DROP_PSPOLL;
	}
	run_write(sc, RT2860_RX_FILTR_CFG, tmp);

	run_write(sc, RT2860_MAC_SYS_CTRL,
	    RT2860_MAC_RX_EN | RT2860_MAC_TX_EN);

	return (0);
}