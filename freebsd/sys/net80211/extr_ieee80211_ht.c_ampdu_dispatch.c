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
struct mbuf {int /*<<< orphan*/  m_flags; } ;
struct ieee80211_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_AMPDU_MPDU ; 
 int /*<<< orphan*/  ieee80211_input (struct ieee80211_node*,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
ampdu_dispatch(struct ieee80211_node *ni, struct mbuf *m)
{
	m->m_flags |= M_AMPDU_MPDU;	/* bypass normal processing */
	/* NB: rssi and noise are ignored w/ M_AMPDU_MPDU set */
	(void) ieee80211_input(ni, m, 0, 0);
}