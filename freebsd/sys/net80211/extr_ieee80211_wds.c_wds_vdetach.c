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
struct ieee80211vap {TYPE_1__* iv_bss; } ;
struct TYPE_2__ {struct ieee80211vap* ni_wdsvap; } ;

/* Variables and functions */

__attribute__((used)) static void
wds_vdetach(struct ieee80211vap *vap)
{
	if (vap->iv_bss != NULL) {
		/* XXX locking? */
		if (vap->iv_bss->ni_wdsvap == vap)
			vap->iv_bss->ni_wdsvap = NULL;
	}
}