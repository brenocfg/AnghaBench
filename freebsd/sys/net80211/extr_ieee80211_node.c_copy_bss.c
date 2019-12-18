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
struct ieee80211_node {int /*<<< orphan*/  ni_vlan; int /*<<< orphan*/  ni_txpower; int /*<<< orphan*/  ni_authmode; } ;

/* Variables and functions */

__attribute__((used)) static __inline void
copy_bss(struct ieee80211_node *nbss, const struct ieee80211_node *obss)
{
	/* propagate useful state */
	nbss->ni_authmode = obss->ni_authmode;
	nbss->ni_txpower = obss->ni_txpower;
	nbss->ni_vlan = obss->ni_vlan;
	/* XXX statistics? */
	/* XXX legacy WDS bssid? */
}