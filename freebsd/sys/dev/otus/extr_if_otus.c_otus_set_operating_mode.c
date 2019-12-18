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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct ieee80211com {int ic_opmode; int /*<<< orphan*/ * ic_macaddr; int /*<<< orphan*/  ic_vaps; } ;
struct otus_softc {struct ieee80211com sc_ic; } ;
struct ieee80211vap {int /*<<< orphan*/  iv_bss; int /*<<< orphan*/ * iv_myaddr; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_bssid; } ;

/* Variables and functions */
 int AR_MAC_CAM_DEFAULTS ; 
 int AR_MAC_CAM_STA ; 
 int /*<<< orphan*/  AR_MAC_REG_CAM_MODE ; 
 int /*<<< orphan*/  AR_MAC_REG_ENCRYPTION ; 
 int /*<<< orphan*/  AR_MAC_REG_RX_CONTROL ; 
 int /*<<< orphan*/  AR_MAC_REG_SNIFFER ; 
 int AR_MAC_RX_CTRL_DEAGG ; 
 int AR_MAC_RX_CTRL_PASS_TO_HOST ; 
 int AR_MAC_RX_CTRL_SHORT_FILTER ; 
 int AR_MAC_SNIFFER_DEFAULTS ; 
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IEEE80211_ADDR_LEN ; 
#define  IEEE80211_M_MONITOR 129 
#define  IEEE80211_M_STA 128 
 int /*<<< orphan*/  OTUS_LOCK_ASSERT (struct otus_softc*) ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 struct ieee80211_node* ieee80211_ref_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otus_set_bssid (struct otus_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  otus_set_macaddr (struct otus_softc*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  otus_write (struct otus_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zero_macaddr ; 

__attribute__((used)) static void
otus_set_operating_mode(struct otus_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap;
	uint32_t cam_mode = AR_MAC_CAM_DEFAULTS;
	uint32_t rx_ctrl = AR_MAC_RX_CTRL_DEAGG | AR_MAC_RX_CTRL_SHORT_FILTER;
	uint32_t sniffer = AR_MAC_SNIFFER_DEFAULTS;
	uint32_t enc_mode = 0x78; /* XXX */
	const uint8_t *macaddr;
	uint8_t bssid[IEEE80211_ADDR_LEN];
	struct ieee80211_node *ni;

	OTUS_LOCK_ASSERT(sc);

	/*
	 * If we're in sniffer mode or we don't have a MAC
	 * address assigned, ensure it gets reset to all-zero.
	 */
	IEEE80211_ADDR_COPY(bssid, zero_macaddr);
	vap = TAILQ_FIRST(&ic->ic_vaps);
	macaddr = vap ? vap->iv_myaddr : ic->ic_macaddr;

	switch (ic->ic_opmode) {
	case IEEE80211_M_STA:
		if (vap) {
			ni = ieee80211_ref_node(vap->iv_bss);
			IEEE80211_ADDR_COPY(bssid, ni->ni_bssid);
			ieee80211_free_node(ni);
		}
		cam_mode |= AR_MAC_CAM_STA;
		rx_ctrl |= AR_MAC_RX_CTRL_PASS_TO_HOST;
		break;
	case IEEE80211_M_MONITOR:
		/*
		 * Note: monitor mode ends up causing the MAC to
		 * generate ACK frames for everything it sees.
		 * So don't do that; instead just put it in STA mode
		 * and disable RX filters.
		 */
	default:
		cam_mode |= AR_MAC_CAM_STA;
		rx_ctrl |= AR_MAC_RX_CTRL_PASS_TO_HOST;
		break;
	}

	/*
	 * TODO: if/when we do hardware encryption, ensure it's
	 * disabled if the NIC is in monitor mode.
	 */
	otus_write(sc, AR_MAC_REG_SNIFFER, sniffer);
	otus_write(sc, AR_MAC_REG_CAM_MODE, cam_mode);
	otus_write(sc, AR_MAC_REG_ENCRYPTION, enc_mode);
	otus_write(sc, AR_MAC_REG_RX_CONTROL, rx_ctrl);
	otus_set_macaddr(sc, macaddr);
	otus_set_bssid(sc, bssid);
	/* XXX barrier? */
}