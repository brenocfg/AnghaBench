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
struct ieee80211_node_table {int dummy; } ;
struct ieee80211_node {int ni_authmode; int ni_flags; int ni_associd; int ni_txpower; int ni_vlan; int* ni_txseqs; int* ni_rxseqs; int ni_rxfragstamp; int ni_noise; int ni_intval; int ni_capinfo; char* ni_esslen; int ni_essid; int ni_inact; int ni_inact_reload; int ni_txrate; int ni_htcap; int ni_htparam; int ni_htctlchan; int ni_ht2ndchan; int ni_htopmode; int ni_htstbc; int ni_chw; int ni_vhtcap; scalar_t__ ni_vht_basicmcs; scalar_t__ ni_vht_chan2; scalar_t__ ni_vht_chan1; TYPE_1__* ni_chan; int /*<<< orphan*/  ni_bssid; int /*<<< orphan*/  ni_macaddr; } ;
struct TYPE_2__ {int ic_freq; int /*<<< orphan*/  ic_flags; } ;

/* Variables and functions */
 size_t IEEE80211_NONQOS_TID ; 
 int IEEE80211_SEQ_FRAG_MASK ; 
 int IEEE80211_SEQ_SEQ_SHIFT ; 
 char* ether_sprintf (int /*<<< orphan*/ ) ; 
 int ieee80211_node_refcnt (struct ieee80211_node*) ; 
 int node_getrssi (struct ieee80211_node*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
ieee80211_dump_node(struct ieee80211_node_table *nt, struct ieee80211_node *ni)
{
	printf("0x%p: mac %s refcnt %d\n", ni,
		ether_sprintf(ni->ni_macaddr), ieee80211_node_refcnt(ni));
	printf("\tauthmode %u flags 0x%x\n",
		ni->ni_authmode, ni->ni_flags);
	printf("\tassocid 0x%x txpower %u vlan %u\n",
		ni->ni_associd, ni->ni_txpower, ni->ni_vlan);
	printf("\ttxseq %u rxseq %u fragno %u rxfragstamp %u\n",
		ni->ni_txseqs[IEEE80211_NONQOS_TID],
		ni->ni_rxseqs[IEEE80211_NONQOS_TID] >> IEEE80211_SEQ_SEQ_SHIFT,
		ni->ni_rxseqs[IEEE80211_NONQOS_TID] & IEEE80211_SEQ_FRAG_MASK,
		ni->ni_rxfragstamp);
	printf("\trssi %d noise %d intval %u capinfo 0x%x\n",
		node_getrssi(ni), ni->ni_noise,
		ni->ni_intval, ni->ni_capinfo);
	printf("\tbssid %s essid \"%.*s\" channel %u:0x%x\n",
		ether_sprintf(ni->ni_bssid),
		ni->ni_esslen, ni->ni_essid,
		ni->ni_chan->ic_freq, ni->ni_chan->ic_flags);
	printf("\tinact %u inact_reload %u txrate %u\n",
		ni->ni_inact, ni->ni_inact_reload, ni->ni_txrate);
	printf("\thtcap %x htparam %x htctlchan %u ht2ndchan %u\n",
		ni->ni_htcap, ni->ni_htparam,
		ni->ni_htctlchan, ni->ni_ht2ndchan);
	printf("\thtopmode %x htstbc %x htchw %u\n",
		ni->ni_htopmode, ni->ni_htstbc, ni->ni_chw);
	printf("\tvhtcap %x freq1 %d freq2 %d vhtbasicmcs %x\n",
		ni->ni_vhtcap, (int) ni->ni_vht_chan1, (int) ni->ni_vht_chan2,
		(int) ni->ni_vht_basicmcs);
	/* XXX VHT state */
}