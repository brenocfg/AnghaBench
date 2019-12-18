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
struct TYPE_2__ {scalar_t__ rs_nrates; } ;
struct ieee80211_node {int /*<<< orphan*/ * ni_chan; TYPE_1__ ni_htrates; } ;

/* Variables and functions */
 int /*<<< orphan*/ * IEEE80211_CHAN_ANYC ; 
 int IEEE80211_IS_CHAN_HT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
amrr_node_is_11n(struct ieee80211_node *ni)
{

	if (ni->ni_chan == NULL)
		return (0);
	if (ni->ni_chan == IEEE80211_CHAN_ANYC)
		return (0);
	if (IEEE80211_IS_CHAN_HT(ni->ni_chan) && ni->ni_htrates.rs_nrates == 0)
		return (0);
	return (IEEE80211_IS_CHAN_HT(ni->ni_chan));
}