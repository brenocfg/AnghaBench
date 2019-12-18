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
struct rum_vap {int /*<<< orphan*/  ratectl_task; struct ieee80211vap vap; } ;
struct ieee80211com {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_runtask (struct ieee80211com*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rum_ratectl_timeout(void *arg)
{
	struct rum_vap *rvp = arg;
	struct ieee80211vap *vap = &rvp->vap;
	struct ieee80211com *ic = vap->iv_ic;

	ieee80211_runtask(ic, &rvp->ratectl_task);
}