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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct rtwn_softc {int dummy; } ;
struct r92c_rx_stat {int /*<<< orphan*/  rxdw4; int /*<<< orphan*/  rxdw3; int /*<<< orphan*/  rxdw1; int /*<<< orphan*/  rxdw0; } ;
struct r12a_rx_phystat {int* cfosho; int /*<<< orphan*/  phyw1; } ;
struct ieee80211_rx_stats {size_t c_rate; int r_flags; int c_ieee; int /*<<< orphan*/  c_freq; int /*<<< orphan*/  c_pktflags; int /*<<< orphan*/  c_phytype; int /*<<< orphan*/  c_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHAN_2GHZ ; 
 int /*<<< orphan*/  IEEE80211_CHAN_5GHZ ; 
 size_t IEEE80211_RATE_MCS ; 
 int /*<<< orphan*/  IEEE80211_RX_FP_11A ; 
 int /*<<< orphan*/  IEEE80211_RX_FP_11B ; 
 int /*<<< orphan*/  IEEE80211_RX_FP_11G ; 
 int /*<<< orphan*/  IEEE80211_RX_FP_11NA ; 
 int /*<<< orphan*/  IEEE80211_RX_FP_11NG ; 
 int /*<<< orphan*/  IEEE80211_RX_FW_20MHZ ; 
 int /*<<< orphan*/  IEEE80211_RX_FW_40MHZ ; 
 int /*<<< orphan*/  IEEE80211_RX_FW_80MHZ ; 
 int /*<<< orphan*/  IEEE80211_RX_F_AMPDU ; 
 int /*<<< orphan*/  IEEE80211_RX_F_AMPDU_MORE ; 
 int /*<<< orphan*/  IEEE80211_RX_F_CCK ; 
 int /*<<< orphan*/  IEEE80211_RX_F_HT ; 
 int /*<<< orphan*/  IEEE80211_RX_F_LDPC ; 
 int /*<<< orphan*/  IEEE80211_RX_F_OFDM ; 
 int /*<<< orphan*/  IEEE80211_RX_F_SHORTGI ; 
 int IEEE80211_R_FREQ ; 
 int IEEE80211_R_IEEE ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R12A_PHYW1_CHAN ; 
 int R12A_RXDW1_AMPDU ; 
 int /*<<< orphan*/  R12A_RXDW3_RATE ; 
 int /*<<< orphan*/  R12A_RXDW4_BW ; 
#define  R12A_RXDW4_BW20 130 
#define  R12A_RXDW4_BW40 129 
#define  R12A_RXDW4_BW80 128 
 int R12A_RXDW4_LDPC ; 
 int R12A_RXDW4_SPLCP ; 
 int R92C_RXDW0_PHYST ; 
 scalar_t__ RTWN_RATE_IS_CCK (size_t) ; 
 size_t RTWN_RIDX_HT_MCS (int /*<<< orphan*/ ) ; 
 size_t RTWN_RIDX_HT_MCS_SHIFT ; 
 int /*<<< orphan*/  ieee80211_ieee2mhz (int,int /*<<< orphan*/ ) ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 size_t* ridx2rate ; 

void
r12a_get_rx_stats(struct rtwn_softc *sc, struct ieee80211_rx_stats *rxs,
    const void *desc, const void *physt_ptr)
{
	const struct r92c_rx_stat *stat = desc;
	const struct r12a_rx_phystat *physt = physt_ptr;
	uint32_t rxdw0, rxdw1, rxdw3, rxdw4;
	uint8_t rate;

	rxdw0 = le32toh(stat->rxdw0);
	rxdw1 = le32toh(stat->rxdw1);
	rxdw3 = le32toh(stat->rxdw3);
	rxdw4 = le32toh(stat->rxdw4);
	rate = MS(rxdw3, R12A_RXDW3_RATE);

	/* TODO: STBC */
	if (rxdw4 & R12A_RXDW4_LDPC)
		rxs->c_pktflags |= IEEE80211_RX_F_LDPC;
	if (rxdw1 & R12A_RXDW1_AMPDU) {
		if (rxdw0 & R92C_RXDW0_PHYST)
			rxs->c_pktflags |= IEEE80211_RX_F_AMPDU;
		else
			rxs->c_pktflags |= IEEE80211_RX_F_AMPDU_MORE;
	}

	if ((rxdw4 & R12A_RXDW4_SPLCP) && rate >= RTWN_RIDX_HT_MCS(0))
		rxs->c_pktflags |= IEEE80211_RX_F_SHORTGI;

	switch (MS(rxdw4, R12A_RXDW4_BW)) {
	case R12A_RXDW4_BW20:
		rxs->c_width = IEEE80211_RX_FW_20MHZ;
		break;
	case R12A_RXDW4_BW40:
		rxs->c_width = IEEE80211_RX_FW_40MHZ;
		break;
	case R12A_RXDW4_BW80:
		rxs->c_width = IEEE80211_RX_FW_80MHZ;
		break;
	default:
		break;
	}

	if (RTWN_RATE_IS_CCK(rate))
		rxs->c_phytype = IEEE80211_RX_FP_11B;
	else {
		int is5ghz;

		/* XXX magic */
		/* XXX check with RTL8812AU */
		is5ghz = (physt->cfosho[2] != 0x01);

		if (rate < RTWN_RIDX_HT_MCS(0)) {
			if (is5ghz)
				rxs->c_phytype = IEEE80211_RX_FP_11A;
			else
				rxs->c_phytype = IEEE80211_RX_FP_11G;
		} else {
			if (is5ghz)
				rxs->c_phytype = IEEE80211_RX_FP_11NA;
			else
				rxs->c_phytype = IEEE80211_RX_FP_11NG;
		}
	}

	/* Map HW rate index to 802.11 rate. */
	if (rate < RTWN_RIDX_HT_MCS(0)) {
		rxs->c_rate = ridx2rate[rate];
		if (RTWN_RATE_IS_CCK(rate))
			rxs->c_pktflags |= IEEE80211_RX_F_CCK;
		else
			rxs->c_pktflags |= IEEE80211_RX_F_OFDM;
	} else {	/* MCS0~15. */
		/* TODO: VHT rates */
		rxs->c_rate =
		    IEEE80211_RATE_MCS | (rate - RTWN_RIDX_HT_MCS_SHIFT);
		rxs->c_pktflags |= IEEE80211_RX_F_HT;
	}

	/*
	 * XXX always zero for RTL8821AU
	 * (vendor driver does not check this field)
	 */
#if 0
	rxs->r_flags |= IEEE80211_R_IEEE | IEEE80211_R_FREQ;
	rxs->c_ieee = MS(le16toh(physt->phyw1), R12A_PHYW1_CHAN);
	rxs->c_freq = ieee80211_ieee2mhz(rxs->c_ieee,
	    (rxs->c_ieee < 36) ? IEEE80211_CHAN_2GHZ : IEEE80211_CHAN_5GHZ);
#endif
}