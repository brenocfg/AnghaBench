#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  is_rx_dup; int /*<<< orphan*/  is_ampdu_rx_reorder; } ;
struct ieee80211vap {TYPE_2__ iv_stats; } ;
struct ieee80211_rx_ampdu {scalar_t__ rxa_wnd; int /*<<< orphan*/  rxa_start; int /*<<< orphan*/  rxa_qbytes; int /*<<< orphan*/  rxa_qframes; struct mbuf** rxa_m; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_macaddr; struct ieee80211vap* ni_vap; } ;
typedef  int /*<<< orphan*/  ieee80211_seq ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_DISCARD_MAC (struct ieee80211vap*,int,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IEEE80211_MSG_11N ; 
 int IEEE80211_MSG_INPUT ; 
 int /*<<< orphan*/  IEEE80211_NODE_STAT (struct ieee80211_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_SEQ_ADD (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  rx_dup ; 

__attribute__((used)) static int
ampdu_rx_add_slot(struct ieee80211_rx_ampdu *rap, int off, int tid,
    ieee80211_seq rxseq,
    struct ieee80211_node *ni,
    struct mbuf *m)
{
	struct ieee80211vap *vap = ni->ni_vap;

	if (rap->rxa_m[off] == NULL) {
		rap->rxa_m[off] = m;
		rap->rxa_qframes++;
		rap->rxa_qbytes += m->m_pkthdr.len;
		vap->iv_stats.is_ampdu_rx_reorder++;
		return (0);
	} else {
		IEEE80211_DISCARD_MAC(vap,
		    IEEE80211_MSG_INPUT | IEEE80211_MSG_11N,
		    ni->ni_macaddr, "a-mpdu duplicate",
		    "seqno %u tid %u BA win <%u:%u>",
		    rxseq, tid, rap->rxa_start,
		    IEEE80211_SEQ_ADD(rap->rxa_start, rap->rxa_wnd-1));
		vap->iv_stats.is_rx_dup++;
		IEEE80211_NODE_STAT(ni, rx_dup);
		m_freem(m);
		return (-1);
	}
}