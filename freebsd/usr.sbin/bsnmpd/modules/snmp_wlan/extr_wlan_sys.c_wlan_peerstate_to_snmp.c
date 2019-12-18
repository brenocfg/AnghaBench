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
 int IEEE80211_NODE_AMPDU_RX ; 
 int IEEE80211_NODE_AMPDU_TX ; 
 int IEEE80211_NODE_AMSDU_RX ; 
 int IEEE80211_NODE_AMSDU_TX ; 
 int IEEE80211_NODE_AREF ; 
 int IEEE80211_NODE_AUTH ; 
 int IEEE80211_NODE_ERP ; 
 int IEEE80211_NODE_HT ; 
 int IEEE80211_NODE_HTCOMPAT ; 
 int IEEE80211_NODE_MIMO_PS ; 
 int IEEE80211_NODE_MIMO_RTS ; 
 int IEEE80211_NODE_PWR_MGT ; 
 int IEEE80211_NODE_QOS ; 
 int IEEE80211_NODE_RIFS ; 
 int IEEE80211_NODE_SGI20 ; 
 int IEEE80211_NODE_SGI40 ; 
 int IEEE80211_NODE_TSN ; 
 int IEEE80211_NODE_WPS ; 
 int WlanIfacePeerFlagsType_ampduRx ; 
 int WlanIfacePeerFlagsType_ampduTx ; 
 int WlanIfacePeerFlagsType_amsduRx ; 
 int WlanIfacePeerFlagsType_amsduTx ; 
 int WlanIfacePeerFlagsType_authRefHeld ; 
 int WlanIfacePeerFlagsType_authorizedForData ; 
 int WlanIfacePeerFlagsType_erpEnabled ; 
 int WlanIfacePeerFlagsType_htCompat ; 
 int WlanIfacePeerFlagsType_htEnabled ; 
 int WlanIfacePeerFlagsType_mimoPowerSave ; 
 int WlanIfacePeerFlagsType_powerSaveMode ; 
 int WlanIfacePeerFlagsType_qosEnabled ; 
 int WlanIfacePeerFlagsType_rifs ; 
 int WlanIfacePeerFlagsType_sendRts ; 
 int WlanIfacePeerFlagsType_shortGiHT20 ; 
 int WlanIfacePeerFlagsType_shortGiHT40 ; 
 int WlanIfacePeerFlagsType_tsnAssoc ; 
 int WlanIfacePeerFlagsType_wpsAssoc ; 

__attribute__((used)) static uint32_t
wlan_peerstate_to_snmp(uint32_t pstate)
{
	uint32_t sstate = 0;

	if ((pstate & IEEE80211_NODE_AUTH) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_authorizedForData);
	if ((pstate & IEEE80211_NODE_QOS) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_qosEnabled);
	if ((pstate & IEEE80211_NODE_ERP) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_erpEnabled);
	if ((pstate & IEEE80211_NODE_PWR_MGT) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_powerSaveMode);
	if ((pstate & IEEE80211_NODE_AREF) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_authRefHeld);
	if ((pstate & IEEE80211_NODE_HT) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_htEnabled);
	if ((pstate & IEEE80211_NODE_HTCOMPAT) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_htCompat);
	if ((pstate & IEEE80211_NODE_WPS) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_wpsAssoc);
	if ((pstate & IEEE80211_NODE_TSN) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_tsnAssoc);
	if ((pstate & IEEE80211_NODE_AMPDU_RX) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_ampduRx);
	if ((pstate & IEEE80211_NODE_AMPDU_TX) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_ampduTx);
	if ((pstate & IEEE80211_NODE_MIMO_PS) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_mimoPowerSave);
	if ((pstate & IEEE80211_NODE_MIMO_RTS) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_sendRts);
	if ((pstate & IEEE80211_NODE_RIFS) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_rifs);
	if ((pstate & IEEE80211_NODE_SGI20) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_shortGiHT20);
	if ((pstate & IEEE80211_NODE_SGI40) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_shortGiHT40);
	if ((pstate & IEEE80211_NODE_AMSDU_RX) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_amsduRx);
	if ((pstate & IEEE80211_NODE_AMSDU_TX) != 0)
		sstate |= (0x1 << WlanIfacePeerFlagsType_amsduTx);

	return (sstate);
}