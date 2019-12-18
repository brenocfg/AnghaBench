#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int tx_mcs_map; int /*<<< orphan*/  rx_mcs_map; } ;
struct ieee80211vap {int iv_flags_vht; int iv_flags_ht; TYPE_1__ iv_vht_mcsinfo; int /*<<< orphan*/  iv_vhtcaps; } ;
struct TYPE_5__ {int tx_mcs_map; } ;
struct ieee80211_node {TYPE_2__ ni_vht_mcsinfo; int /*<<< orphan*/  ni_vhtcap; struct ieee80211vap* ni_vap; } ;
struct TYPE_6__ {int tx_mcs_map; scalar_t__ tx_highest; scalar_t__ rx_highest; int /*<<< orphan*/  rx_mcs_map; } ;
struct ieee80211_ie_vhtcap {int len; int vht_cap_info; TYPE_3__ supp_mcs; int /*<<< orphan*/  ie; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ELEMID_VHT_CAP ; 
 int IEEE80211_FHT_STBC_RX ; 
 int IEEE80211_FHT_STBC_TX ; 
 int IEEE80211_FVHT_USEVHT160 ; 
 int IEEE80211_FVHT_USEVHT80P80 ; 
 int IEEE80211_VHTCAP_BEAMFORMEE_STS_MASK ; 
 int IEEE80211_VHTCAP_HTC_VHT ; 
 int IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK ; 
 int IEEE80211_VHTCAP_MAX_MPDU_MASK ; 
 int IEEE80211_VHTCAP_MU_BEAMFORMEE_CAPABLE ; 
 int IEEE80211_VHTCAP_MU_BEAMFORMER_CAPABLE ; 
 int IEEE80211_VHTCAP_RXLDPC ; 
 int IEEE80211_VHTCAP_RXSTBC_MASK ; 
 int IEEE80211_VHTCAP_RX_ANTENNA_PATTERN ; 
 int IEEE80211_VHTCAP_SHORT_GI_160 ; 
 int IEEE80211_VHTCAP_SHORT_GI_80 ; 
 int IEEE80211_VHTCAP_SOUNDING_DIMENSIONS_MASK ; 
 int IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK ; 
 int IEEE80211_VHTCAP_SU_BEAMFORMEE_CAPABLE ; 
 int IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE ; 
 int IEEE80211_VHTCAP_TXSTBC ; 
 int IEEE80211_VHTCAP_TX_ANTENNA_PATTERN ; 
 int IEEE80211_VHTCAP_VHT_LINK_ADAPTATION_VHT_MASK ; 
 int IEEE80211_VHTCAP_VHT_TXOP_PS ; 
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 int MS (int /*<<< orphan*/ ,int) ; 
 int SM (int,int) ; 

void
ieee80211_vht_get_vhtcap_ie(struct ieee80211_node *ni,
    struct ieee80211_ie_vhtcap *vhtcap, int opmode)
{
	struct ieee80211vap *vap = ni->ni_vap;
//	struct ieee80211com *ic = vap->iv_ic;
	uint32_t val, val1, val2;
	uint32_t new_vhtcap;
	int i;

	vhtcap->ie = IEEE80211_ELEMID_VHT_CAP;
	vhtcap->len = sizeof(struct ieee80211_ie_vhtcap) - 2;

	/*
	 * Capabilities - it depends on whether we are a station
	 * or not.
	 */
	new_vhtcap = 0;

	/*
	 * Station - use our desired configuration based on
	 * local config, local device bits and the already-learnt
	 * vhtcap/vhtinfo IE in the node.
	 */

	/* Limit MPDU size to the smaller of the two */
	val2 = val1 = MS(vap->iv_vhtcaps, IEEE80211_VHTCAP_MAX_MPDU_MASK);
	if (opmode == 1) {
		val2 = MS(ni->ni_vhtcap, IEEE80211_VHTCAP_MAX_MPDU_MASK);
	}
	val = MIN(val1, val2);
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_MAX_MPDU_MASK);

	/* Limit supp channel config */
	val2 = val1 = MS(vap->iv_vhtcaps,
	    IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK);
	if (opmode == 1) {
		val2 = MS(ni->ni_vhtcap,
		    IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK);
	}
	if ((val2 == 2) &&
	    ((vap->iv_flags_vht & IEEE80211_FVHT_USEVHT80P80) == 0))
		val2 = 1;
	if ((val2 == 1) &&
	    ((vap->iv_flags_vht & IEEE80211_FVHT_USEVHT160) == 0))
		val2 = 0;
	val = MIN(val1, val2);
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK);

	/* RX LDPC */
	val2 = val1 = MS(vap->iv_vhtcaps, IEEE80211_VHTCAP_RXLDPC);
	if (opmode == 1) {
		val2 = MS(ni->ni_vhtcap, IEEE80211_VHTCAP_RXLDPC);
	}
	val = MIN(val1, val2);
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_RXLDPC);

	/* Short-GI 80 */
	val2 = val1 = MS(vap->iv_vhtcaps, IEEE80211_VHTCAP_SHORT_GI_80);
	if (opmode == 1) {
		val2 = MS(ni->ni_vhtcap, IEEE80211_VHTCAP_SHORT_GI_80);
	}
	val = MIN(val1, val2);
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_SHORT_GI_80);

	/* Short-GI 160 */
	val2 = val1 = MS(vap->iv_vhtcaps, IEEE80211_VHTCAP_SHORT_GI_160);
	if (opmode == 1) {
		val2 = MS(ni->ni_vhtcap, IEEE80211_VHTCAP_SHORT_GI_160);
	}
	val = MIN(val1, val2);
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_SHORT_GI_160);

	/*
	 * STBC is slightly more complicated.
	 *
	 * In non-STA mode, we just announce our capabilities and that
	 * is that.
	 *
	 * In STA mode, we should calculate our capabilities based on
	 * local capabilities /and/ what the remote says. So:
	 *
	 * + Only TX STBC if we support it and the remote supports RX STBC;
	 * + Only announce RX STBC if we support it and the remote supports
	 *   TX STBC;
	 * + RX STBC should be the minimum of local and remote RX STBC;
	 */

	/* TX STBC */
	val2 = val1 = MS(vap->iv_vhtcaps, IEEE80211_VHTCAP_TXSTBC);
	if (opmode == 1) {
		/* STA mode - enable it only if node RXSTBC is non-zero */
		val2 = !! MS(ni->ni_vhtcap, IEEE80211_VHTCAP_RXSTBC_MASK);
	}
	val = MIN(val1, val2);
	/* XXX For now, use the 11n config flag */
	if ((vap->iv_flags_ht & IEEE80211_FHT_STBC_TX) == 0)
		val = 0;
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_TXSTBC);

	/* RX STBC1..4 */
	val2 = val1 = MS(vap->iv_vhtcaps, IEEE80211_VHTCAP_RXSTBC_MASK);
	if (opmode == 1) {
		/* STA mode - enable it only if node TXSTBC is non-zero */
		val2 = MS(ni->ni_vhtcap, IEEE80211_VHTCAP_TXSTBC);
	}
	val = MIN(val1, val2);
	/* XXX For now, use the 11n config flag */
	if ((vap->iv_flags_ht & IEEE80211_FHT_STBC_RX) == 0)
		val = 0;
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_RXSTBC_MASK);

	/*
	 * Finally - if RXSTBC is 0, then don't enable TXSTBC.
	 * Strictly speaking a device can TXSTBC and not RXSTBC, but
	 * it would be silly.
	 */
	if (val == 0)
		new_vhtcap &= ~IEEE80211_VHTCAP_TXSTBC;

	/*
	 * Some of these fields require other fields to exist.
	 * So before using it, the parent field needs to be checked
	 * otherwise the overridden value may be wrong.
	 *
	 * For example, if SU beamformee is set to 0, then BF STS
	 * needs to be 0.
	 */

	/* SU Beamformer capable */
	val2 = val1 = MS(vap->iv_vhtcaps,
	    IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE);
	if (opmode == 1) {
		val2 = MS(ni->ni_vhtcap,
		    IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE);
	}
	val = MIN(val1, val2);
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE);

	/* SU Beamformee capable */
	val2 = val1 = MS(vap->iv_vhtcaps,
	    IEEE80211_VHTCAP_SU_BEAMFORMEE_CAPABLE);
	if (opmode == 1) {
		val2 = MS(ni->ni_vhtcap,
		    IEEE80211_VHTCAP_SU_BEAMFORMEE_CAPABLE);
	}
	val = MIN(val1, val2);
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_SU_BEAMFORMEE_CAPABLE);

	/* Beamformee STS capability - only if SU beamformee capable */
	val2 = val1 = MS(vap->iv_vhtcaps, IEEE80211_VHTCAP_BEAMFORMEE_STS_MASK);
	if (opmode == 1) {
		val2 = MS(ni->ni_vhtcap, IEEE80211_VHTCAP_BEAMFORMEE_STS_MASK);
	}
	val = MIN(val1, val2);
	if ((new_vhtcap & IEEE80211_VHTCAP_SU_BEAMFORMEE_CAPABLE) == 0)
		val = 0;
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_BEAMFORMEE_STS_MASK);

	/* Sounding dimensions - only if SU beamformer capable */
	val2 = val1 = MS(vap->iv_vhtcaps,
	    IEEE80211_VHTCAP_SOUNDING_DIMENSIONS_MASK);
	if (opmode == 1)
		val2 = MS(ni->ni_vhtcap,
		    IEEE80211_VHTCAP_SOUNDING_DIMENSIONS_MASK);
	val = MIN(val1, val2);
	if ((new_vhtcap & IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE) == 0)
		val = 0;
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_SOUNDING_DIMENSIONS_MASK);

	/*
	 * MU Beamformer capable - only if SU BFF capable, MU BFF capable
	 * and STA (not AP)
	 */
	val2 = val1 = MS(vap->iv_vhtcaps,
	    IEEE80211_VHTCAP_MU_BEAMFORMER_CAPABLE);
	if (opmode == 1)
		val2 = MS(ni->ni_vhtcap,
		    IEEE80211_VHTCAP_MU_BEAMFORMER_CAPABLE);
	val = MIN(val1, val2);
	if ((new_vhtcap & IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE) == 0)
		val = 0;
	if (opmode != 1)	/* Only enable for STA mode */
		val = 0;
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE);

	/*
	 * MU Beamformee capable - only if SU BFE capable, MU BFE capable
	 * and AP (not STA)
	 */
	val2 = val1 = MS(vap->iv_vhtcaps,
	    IEEE80211_VHTCAP_MU_BEAMFORMEE_CAPABLE);
	if (opmode == 1)
		val2 = MS(ni->ni_vhtcap,
		    IEEE80211_VHTCAP_MU_BEAMFORMEE_CAPABLE);
	val = MIN(val1, val2);
	if ((new_vhtcap & IEEE80211_VHTCAP_SU_BEAMFORMEE_CAPABLE) == 0)
		val = 0;
	if (opmode != 0)	/* Only enable for AP mode */
		val = 0;
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_SU_BEAMFORMEE_CAPABLE);

	/* VHT TXOP PS */
	val2 = val1 = MS(vap->iv_vhtcaps, IEEE80211_VHTCAP_VHT_TXOP_PS);
	if (opmode == 1)
		val2 = MS(ni->ni_vhtcap, IEEE80211_VHTCAP_VHT_TXOP_PS);
	val = MIN(val1, val2);
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_VHT_TXOP_PS);

	/* HTC_VHT */
	val2 = val1 = MS(vap->iv_vhtcaps, IEEE80211_VHTCAP_HTC_VHT);
	if (opmode == 1)
		val2 = MS(ni->ni_vhtcap, IEEE80211_VHTCAP_HTC_VHT);
	val = MIN(val1, val2);
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_HTC_VHT);

	/* A-MPDU length max */
	/* XXX TODO: we need a userland config knob for this */
	val2 = val1 = MS(vap->iv_vhtcaps,
	    IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK);
	if (opmode == 1)
		val2 = MS(ni->ni_vhtcap,
		    IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK);
	val = MIN(val1, val2);
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK);

	/*
	 * Link adaptation is only valid if HTC-VHT capable is 1.
	 * Otherwise, always set it to 0.
	 */
	val2 = val1 = MS(vap->iv_vhtcaps,
	    IEEE80211_VHTCAP_VHT_LINK_ADAPTATION_VHT_MASK);
	if (opmode == 1)
		val2 = MS(ni->ni_vhtcap,
		    IEEE80211_VHTCAP_VHT_LINK_ADAPTATION_VHT_MASK);
	val = MIN(val1, val2);
	if ((new_vhtcap & IEEE80211_VHTCAP_HTC_VHT) == 0)
		val = 0;
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_VHT_LINK_ADAPTATION_VHT_MASK);

	/*
	 * The following two options are 0 if the pattern may change, 1 if it
	 * does not change.  So, downgrade to the higher value.
	 */

	/* RX antenna pattern */
	val2 = val1 = MS(vap->iv_vhtcaps, IEEE80211_VHTCAP_RX_ANTENNA_PATTERN);
	if (opmode == 1)
		val2 = MS(ni->ni_vhtcap, IEEE80211_VHTCAP_RX_ANTENNA_PATTERN);
	val = MAX(val1, val2);
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_RX_ANTENNA_PATTERN);

	/* TX antenna pattern */
	val2 = val1 = MS(vap->iv_vhtcaps, IEEE80211_VHTCAP_TX_ANTENNA_PATTERN);
	if (opmode == 1)
		val2 = MS(ni->ni_vhtcap, IEEE80211_VHTCAP_TX_ANTENNA_PATTERN);
	val = MAX(val1, val2);
	new_vhtcap |= SM(val, IEEE80211_VHTCAP_TX_ANTENNA_PATTERN);

	/*
	 * MCS set - again, we announce what we want to use
	 * based on configuration, device capabilities and
	 * already-learnt vhtcap/vhtinfo IE information.
	 */

	/* MCS set - start with whatever the device supports */
	vhtcap->supp_mcs.rx_mcs_map = vap->iv_vht_mcsinfo.rx_mcs_map;
	vhtcap->supp_mcs.rx_highest = 0;
	vhtcap->supp_mcs.tx_mcs_map = vap->iv_vht_mcsinfo.tx_mcs_map;
	vhtcap->supp_mcs.tx_highest = 0;

	vhtcap->vht_cap_info = new_vhtcap;

	/*
	 * Now, if we're a STA, mask off whatever the AP doesn't support.
	 * Ie, we continue to state we can receive whatever we can do,
	 * but we only announce that we will transmit rates that meet
	 * the AP requirement.
	 *
	 * Note: 0 - MCS0..7; 1 - MCS0..8; 2 - MCS0..9; 3 = not supported.
	 * We can't just use MIN() because '3' means "no", so special case it.
	 */
	if (opmode) {
		for (i = 0; i < 8; i++) {
			val1 = (vhtcap->supp_mcs.tx_mcs_map >> (i*2)) & 0x3;
			val2 = (ni->ni_vht_mcsinfo.tx_mcs_map >> (i*2)) & 0x3;
			val = MIN(val1, val2);
			if (val1 == 3 || val2 == 3)
				val = 3;
			vhtcap->supp_mcs.tx_mcs_map &= ~(0x3 << (i*2));
			vhtcap->supp_mcs.tx_mcs_map |= (val << (i*2));
		}
	}
}