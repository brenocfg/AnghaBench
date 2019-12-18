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
struct wtap_vap {int dummy; } ;
struct TYPE_2__ {scalar_t__ rcvif; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;
struct ieee80211vap {int dummy; } ;
struct ieee80211com {int dummy; } ;
struct ieee80211_node {struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int M_TXCB ; 
 struct wtap_vap* WTAP_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_process_callback (struct ieee80211_node*,struct mbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_radiotap_active_vap (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_radiotap_tx (struct ieee80211vap*,struct mbuf*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int wtap_medium_enqueue (struct wtap_vap*,struct mbuf*) ; 

__attribute__((used)) static int
wtap_transmit(struct ieee80211com *ic, struct mbuf *m)
{
	struct ieee80211_node *ni =
	    (struct ieee80211_node *) m->m_pkthdr.rcvif;
	struct ieee80211vap *vap = ni->ni_vap;
	struct wtap_vap *avp = WTAP_VAP(vap);

	if(ni == NULL){
		printf("m->m_pkthdr.rcvif is NULL we cant radiotap_tx\n");
	}else{
		if (ieee80211_radiotap_active_vap(vap))
			ieee80211_radiotap_tx(vap, m);
	}
	if (m->m_flags & M_TXCB)
		ieee80211_process_callback(ni, m, 0);
	ieee80211_free_node(ni);
	return wtap_medium_enqueue(avp, m);
}