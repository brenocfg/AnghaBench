#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wmeParams {int /*<<< orphan*/  wmep_txopLimit; int /*<<< orphan*/  wmep_logcwmax; int /*<<< orphan*/  wmep_logcwmin; int /*<<< orphan*/  wmep_aifsn; int /*<<< orphan*/  wmep_acm; } ;
struct ieee80211vap {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  acm; } ;
typedef  TYPE_1__ paramType ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_DPRINTF (struct ieee80211vap*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_MSG_WME ; 
 int /*<<< orphan*/  _setifsparams (struct wmeParams*,TYPE_1__ const*) ; 
 int /*<<< orphan*/ * ieee80211_wme_acnames ; 

__attribute__((used)) static void
setwmeparams(struct ieee80211vap *vap, const char *type, int ac,
	struct wmeParams *wmep, const paramType *phy)
{
	wmep->wmep_acm = phy->acm;
	_setifsparams(wmep, phy);

	IEEE80211_DPRINTF(vap, IEEE80211_MSG_WME,
	    "set %s (%s) [acm %u aifsn %u logcwmin %u logcwmax %u txop %u]\n",
	    ieee80211_wme_acnames[ac], type,
	    wmep->wmep_acm, wmep->wmep_aifsn, wmep->wmep_logcwmin,
	    wmep->wmep_logcwmax, wmep->wmep_txopLimit);
}