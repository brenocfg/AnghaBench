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
struct ieee80211com {int /*<<< orphan*/  ic_chw_task; int /*<<< orphan*/  ic_curchan; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_runtask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_setupcurchan (struct ieee80211com*,int /*<<< orphan*/ ) ; 

void
ieee80211_update_chw(struct ieee80211com *ic)
{

	ieee80211_setupcurchan(ic, ic->ic_curchan);
	ieee80211_runtask(ic, &ic->ic_chw_task);
}