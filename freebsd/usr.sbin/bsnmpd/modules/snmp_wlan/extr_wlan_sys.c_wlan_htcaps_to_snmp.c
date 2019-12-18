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

/* Variables and functions */
 int IEEE80211_HTCAP_40INTOLERANT ; 
 int IEEE80211_HTCAP_CHWIDTH40 ; 
 int IEEE80211_HTCAP_DELBA ; 
 int IEEE80211_HTCAP_DSSSCCK40 ; 
 int IEEE80211_HTCAP_GREENFIELD ; 
 int IEEE80211_HTCAP_LDPC ; 
 int IEEE80211_HTCAP_LSIGTXOPPROT ; 
 int IEEE80211_HTCAP_MAXAMSDU_7935 ; 
 int IEEE80211_HTCAP_PSMP ; 
 int IEEE80211_HTCAP_SHORTGI20 ; 
 int IEEE80211_HTCAP_SHORTGI40 ; 
 int IEEE80211_HTCAP_TXSTBC ; 
 int IEEE80211_HTC_AMPDU ; 
 int IEEE80211_HTC_AMSDU ; 
 int IEEE80211_HTC_HT ; 
 int IEEE80211_HTC_RIFS ; 
 int IEEE80211_HTC_SMPS ; 
 int WlanHTCaps_amsdu7935 ; 
 int WlanHTCaps_chwidth40 ; 
 int WlanHTCaps_delba ; 
 int WlanHTCaps_dssscck40 ; 
 int WlanHTCaps_fortyMHzIntolerant ; 
 int WlanHTCaps_greenField ; 
 int WlanHTCaps_htcAmpdu ; 
 int WlanHTCaps_htcAmsdu ; 
 int WlanHTCaps_htcHt ; 
 int WlanHTCaps_htcRifs ; 
 int WlanHTCaps_htcSmps ; 
 int WlanHTCaps_ldpc ; 
 int WlanHTCaps_lsigTxOpProt ; 
 int WlanHTCaps_psmp ; 
 int WlanHTCaps_shortGi20 ; 
 int WlanHTCaps_shortGi40 ; 
 int WlanHTCaps_txStbc ; 

__attribute__((used)) static uint32_t
wlan_htcaps_to_snmp(uint32_t hcaps)
{
	uint32_t scaps = 0;

	if ((hcaps & IEEE80211_HTCAP_LDPC) != 0)
		scaps |= (0x1 << WlanHTCaps_ldpc);
	if ((hcaps & IEEE80211_HTCAP_CHWIDTH40) != 0)
		scaps |= (0x1 << WlanHTCaps_chwidth40);
	if ((hcaps & IEEE80211_HTCAP_GREENFIELD) != 0)
		scaps |= (0x1 << WlanHTCaps_greenField);
	if ((hcaps & IEEE80211_HTCAP_SHORTGI20) != 0)
		scaps |= (0x1 << WlanHTCaps_shortGi20);
	if ((hcaps & IEEE80211_HTCAP_SHORTGI40) != 0)
		scaps |= (0x1 << WlanHTCaps_shortGi40);
	if ((hcaps & IEEE80211_HTCAP_TXSTBC) != 0)
		scaps |= (0x1 << WlanHTCaps_txStbc);
	if ((hcaps & IEEE80211_HTCAP_DELBA) != 0)
		scaps |= (0x1 << WlanHTCaps_delba);
	if ((hcaps & IEEE80211_HTCAP_MAXAMSDU_7935) != 0)
		scaps |= (0x1 << WlanHTCaps_amsdu7935);
	if ((hcaps & IEEE80211_HTCAP_DSSSCCK40) != 0)
		scaps |= (0x1 << WlanHTCaps_dssscck40);
	if ((hcaps & IEEE80211_HTCAP_PSMP) != 0)
		scaps |= (0x1 << WlanHTCaps_psmp);
	if ((hcaps & IEEE80211_HTCAP_40INTOLERANT) != 0)
		scaps |= (0x1 << WlanHTCaps_fortyMHzIntolerant);
	if ((hcaps & IEEE80211_HTCAP_LSIGTXOPPROT) != 0)
		scaps |= (0x1 << WlanHTCaps_lsigTxOpProt);
	if ((hcaps & IEEE80211_HTC_AMPDU) != 0)
		scaps |= (0x1 << WlanHTCaps_htcAmpdu);
	if ((hcaps & IEEE80211_HTC_AMSDU) != 0)
		scaps |= (0x1 << WlanHTCaps_htcAmsdu);
	if ((hcaps & IEEE80211_HTC_HT) != 0)
		scaps |= (0x1 << WlanHTCaps_htcHt);
	if ((hcaps & IEEE80211_HTC_SMPS) != 0)
		scaps |= (0x1 << WlanHTCaps_htcSmps);
	if ((hcaps & IEEE80211_HTC_RIFS) != 0)
		scaps |= (0x1 << WlanHTCaps_htcRifs);

	return (scaps);
}