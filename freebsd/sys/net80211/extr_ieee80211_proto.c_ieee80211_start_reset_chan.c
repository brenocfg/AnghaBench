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
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {int /*<<< orphan*/ * ic_channels; int /*<<< orphan*/ * ic_curchan; } ;

/* Variables and functions */

__attribute__((used)) static void
ieee80211_start_reset_chan(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;

	ic->ic_curchan = &ic->ic_channels[0];
}