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
struct ieee80211vap {int iv_amsdu_limit; int iv_htcaps; int* iv_ampdu_mintraffic; int iv_flags_ht; int iv_flags_ext; int /*<<< orphan*/  iv_ampdu_rxmax; int /*<<< orphan*/  iv_ampdu_limit; int /*<<< orphan*/  iv_ampdu_density; } ;

/* Variables and functions */
 int IEEE80211_FEXT_WDSLEGACY ; 
 int IEEE80211_FHT_AMPDU_RX ; 
 int IEEE80211_FHT_AMPDU_TX ; 
 int IEEE80211_FHT_AMSDU_RX ; 
 int IEEE80211_FHT_AMSDU_TX ; 
 int IEEE80211_FHT_HT ; 
 int IEEE80211_FHT_HTCOMPAT ; 
 int IEEE80211_FHT_LDPC_RX ; 
 int IEEE80211_FHT_LDPC_TX ; 
 int IEEE80211_FHT_RIFS ; 
 int IEEE80211_FHT_SHORTGI20 ; 
 int IEEE80211_FHT_SHORTGI40 ; 
 int IEEE80211_FHT_STBC_RX ; 
 int IEEE80211_FHT_STBC_TX ; 
 int IEEE80211_FHT_USEHT40 ; 
 int IEEE80211_HTCAP_CHWIDTH40 ; 
 int IEEE80211_HTCAP_LDPC ; 
 int IEEE80211_HTCAP_MAXAMSDU ; 
 int /*<<< orphan*/  IEEE80211_HTCAP_MAXRXAMPDU_8K ; 
 int /*<<< orphan*/  IEEE80211_HTCAP_MPDUDENSITY_NA ; 
 int IEEE80211_HTCAP_RXSTBC ; 
 int IEEE80211_HTCAP_SHORTGI20 ; 
 int IEEE80211_HTCAP_SHORTGI40 ; 
 int IEEE80211_HTCAP_TXSTBC ; 
 int IEEE80211_HTC_AMPDU ; 
 int IEEE80211_HTC_AMSDU ; 
 int IEEE80211_HTC_HT ; 
 int IEEE80211_HTC_RIFS ; 
 int IEEE80211_HTC_TXLDPC ; 
 size_t WME_AC_BE ; 
 size_t WME_AC_BK ; 
 size_t WME_AC_VI ; 
 size_t WME_AC_VO ; 

void
ieee80211_ht_vattach(struct ieee80211vap *vap)
{

	/* driver can override defaults */
	vap->iv_ampdu_rxmax = IEEE80211_HTCAP_MAXRXAMPDU_8K;
	vap->iv_ampdu_density = IEEE80211_HTCAP_MPDUDENSITY_NA;
	vap->iv_ampdu_limit = vap->iv_ampdu_rxmax;
	vap->iv_amsdu_limit = vap->iv_htcaps & IEEE80211_HTCAP_MAXAMSDU;
	/* tx aggregation traffic thresholds */
	vap->iv_ampdu_mintraffic[WME_AC_BK] = 128;
	vap->iv_ampdu_mintraffic[WME_AC_BE] = 64;
	vap->iv_ampdu_mintraffic[WME_AC_VO] = 32;
	vap->iv_ampdu_mintraffic[WME_AC_VI] = 32;

	if (vap->iv_htcaps & IEEE80211_HTC_HT) {
		/*
		 * Device is HT capable; enable all HT-related
		 * facilities by default.
		 * XXX these choices may be too aggressive.
		 */
		vap->iv_flags_ht |= IEEE80211_FHT_HT
				 |  IEEE80211_FHT_HTCOMPAT
				 ;
		if (vap->iv_htcaps & IEEE80211_HTCAP_SHORTGI20)
			vap->iv_flags_ht |= IEEE80211_FHT_SHORTGI20;
		/* XXX infer from channel list? */
		if (vap->iv_htcaps & IEEE80211_HTCAP_CHWIDTH40) {
			vap->iv_flags_ht |= IEEE80211_FHT_USEHT40;
			if (vap->iv_htcaps & IEEE80211_HTCAP_SHORTGI40)
				vap->iv_flags_ht |= IEEE80211_FHT_SHORTGI40;
		}
		/* enable RIFS if capable */
		if (vap->iv_htcaps & IEEE80211_HTC_RIFS)
			vap->iv_flags_ht |= IEEE80211_FHT_RIFS;

		/* NB: A-MPDU and A-MSDU rx are mandated, these are tx only */
		vap->iv_flags_ht |= IEEE80211_FHT_AMPDU_RX;
		if (vap->iv_htcaps & IEEE80211_HTC_AMPDU)
			vap->iv_flags_ht |= IEEE80211_FHT_AMPDU_TX;
		vap->iv_flags_ht |= IEEE80211_FHT_AMSDU_RX;
		if (vap->iv_htcaps & IEEE80211_HTC_AMSDU)
			vap->iv_flags_ht |= IEEE80211_FHT_AMSDU_TX;

		if (vap->iv_htcaps & IEEE80211_HTCAP_TXSTBC)
			vap->iv_flags_ht |= IEEE80211_FHT_STBC_TX;
		if (vap->iv_htcaps & IEEE80211_HTCAP_RXSTBC)
			vap->iv_flags_ht |= IEEE80211_FHT_STBC_RX;

		if (vap->iv_htcaps & IEEE80211_HTCAP_LDPC)
			vap->iv_flags_ht |= IEEE80211_FHT_LDPC_RX;
		if (vap->iv_htcaps & IEEE80211_HTC_TXLDPC)
			vap->iv_flags_ht |= IEEE80211_FHT_LDPC_TX;
	}
	/* NB: disable default legacy WDS, too many issues right now */
	if (vap->iv_flags_ext & IEEE80211_FEXT_WDSLEGACY)
		vap->iv_flags_ht &= ~IEEE80211_FHT_HT;
}