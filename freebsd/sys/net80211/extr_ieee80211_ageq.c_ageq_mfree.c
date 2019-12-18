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
struct TYPE_2__ {scalar_t__ rcvif; } ;
struct mbuf {int m_flags; int /*<<< orphan*/ * m_nextpkt; TYPE_1__ m_pkthdr; } ;
struct ieee80211_node {int dummy; } ;

/* Variables and functions */
 int M_ENCAP ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void
ageq_mfree(struct mbuf *m)
{
	if (m->m_flags & M_ENCAP) {
		struct ieee80211_node *ni = (void *) m->m_pkthdr.rcvif;
		ieee80211_free_node(ni);
	}
	m->m_nextpkt = NULL;
	m_freem(m);
}