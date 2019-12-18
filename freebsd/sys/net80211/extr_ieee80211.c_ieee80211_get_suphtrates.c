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
struct ieee80211_htrateset {int dummy; } ;
struct ieee80211com {struct ieee80211_htrateset const ic_sup_htrates; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */

const struct ieee80211_htrateset *
ieee80211_get_suphtrates(struct ieee80211com *ic,
    const struct ieee80211_channel *c)
{
	return &ic->ic_sup_htrates;
}