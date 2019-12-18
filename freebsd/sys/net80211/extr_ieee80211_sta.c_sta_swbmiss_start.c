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
struct ieee80211vap {int iv_flags_ext; int iv_bmissthreshold; int /*<<< orphan*/  iv_swbmiss_period; int /*<<< orphan*/  iv_swbmiss; scalar_t__ iv_swbmiss_count; TYPE_1__* iv_bss; } ;
struct TYPE_2__ {int ni_intval; } ;

/* Variables and functions */
 int IEEE80211_FEXT_SWBMISS ; 
 int /*<<< orphan*/  IEEE80211_TU_TO_TICKS (int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_swbmiss ; 

__attribute__((used)) static void
sta_swbmiss_start(struct ieee80211vap *vap)
{

	if (vap->iv_flags_ext & IEEE80211_FEXT_SWBMISS) {
		/*
		 * Start s/w beacon miss timer for devices w/o
		 * hardware support.  We fudge a bit here since
		 * we're doing this in software.
		 */
		vap->iv_swbmiss_period = IEEE80211_TU_TO_TICKS(
		    2 * vap->iv_bmissthreshold * vap->iv_bss->ni_intval);
		vap->iv_swbmiss_count = 0;
		callout_reset(&vap->iv_swbmiss, vap->iv_swbmiss_period,
		    ieee80211_swbmiss, vap);
	}
}