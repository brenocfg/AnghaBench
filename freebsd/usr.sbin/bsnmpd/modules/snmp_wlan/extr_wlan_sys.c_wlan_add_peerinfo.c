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
struct wlan_peer {int /*<<< orphan*/  peer_id; int /*<<< orphan*/  local_id; int /*<<< orphan*/  state; int /*<<< orphan*/  capinfo; int /*<<< orphan*/  txpower; int /*<<< orphan*/  rxseqs; int /*<<< orphan*/  txseqs; int /*<<< orphan*/  idle; int /*<<< orphan*/  rssi; int /*<<< orphan*/  txrate; int /*<<< orphan*/  fflags; int /*<<< orphan*/  frequency; int /*<<< orphan*/  vlan; int /*<<< orphan*/  associd; } ;
struct ieee80211req_sta_info {int /*<<< orphan*/  isi_peerid; int /*<<< orphan*/  isi_localid; int /*<<< orphan*/  isi_state; int /*<<< orphan*/  isi_capinfo; int /*<<< orphan*/  isi_txpower; int /*<<< orphan*/ * isi_rxseqs; int /*<<< orphan*/ * isi_txseqs; int /*<<< orphan*/  isi_inact; int /*<<< orphan*/  isi_rssi; int /*<<< orphan*/  isi_txrate; int /*<<< orphan*/  isi_flags; int /*<<< orphan*/  isi_freq; int /*<<< orphan*/  isi_vlan; int /*<<< orphan*/  isi_associd; int /*<<< orphan*/  isi_macaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AID (int /*<<< orphan*/ ) ; 
 struct wlan_peer* wlan_new_peer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_peercaps_to_snmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_peerstate_to_snmp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wlan_peer *
wlan_add_peerinfo(const struct ieee80211req_sta_info *si)
{
	struct wlan_peer *wip;

	if ((wip = wlan_new_peer(si->isi_macaddr))== NULL)
		return (NULL);

	wip->associd = IEEE80211_AID(si->isi_associd);
	wip->vlan = si->isi_vlan;
	wip->frequency =  si->isi_freq;
	wip->fflags = si->isi_flags;
	wip->txrate = si->isi_txrate;
	wip->rssi = si->isi_rssi;
	wip->idle = si->isi_inact;
	wip->txseqs = si->isi_txseqs[0]; /* XXX */
	wip->rxseqs = si->isi_rxseqs[0]; /* XXX */
	wip->txpower = si->isi_txpower;
	wip->capinfo = wlan_peercaps_to_snmp(si->isi_capinfo);
	wip->state = wlan_peerstate_to_snmp(si->isi_state);
	wip->local_id = si->isi_localid;
	wip->peer_id = si->isi_peerid;

	return (wip);
}