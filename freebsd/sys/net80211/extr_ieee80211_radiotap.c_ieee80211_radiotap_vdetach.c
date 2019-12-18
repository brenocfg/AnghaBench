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
struct ieee80211vap {int dummy; } ;

/* Variables and functions */

void
ieee80211_radiotap_vdetach(struct ieee80211vap *vap)
{
	/* NB: bpfattach is called by ether_ifdetach and claims all taps */
}