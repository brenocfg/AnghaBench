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
struct rtwn_vap {scalar_t__ curr_mode; int /*<<< orphan*/  tsf_sync_adhoc_task; } ;
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {int dummy; } ;

/* Variables and functions */
 scalar_t__ R92C_MSR_NOLINK ; 
 struct rtwn_vap* RTWN_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_runtask (struct ieee80211com*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rtwn_tsf_sync_adhoc(void *arg)
{
	struct ieee80211vap *vap = arg;
	struct ieee80211com *ic = vap->iv_ic;
	struct rtwn_vap *uvp = RTWN_VAP(vap);

	if (uvp->curr_mode != R92C_MSR_NOLINK) {
		/* Do it in process context. */
		ieee80211_runtask(ic, &uvp->tsf_sync_adhoc_task);
	}
}