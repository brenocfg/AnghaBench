#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ieee80211com {int ic_flags; struct ieee80211_scan_state* ic_scan; int /*<<< orphan*/  ic_tq; } ;
struct ieee80211_scan_state {TYPE_1__* ss_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  ss_scan_curchan; int /*<<< orphan*/  ss_scan_start; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* scan_detach ) (struct ieee80211_scan_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FREE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int IEEE80211_F_SCAN ; 
 int /*<<< orphan*/  ISCAN_ABORT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_80211_SCAN ; 
 TYPE_2__* SCAN_PRIVATE (struct ieee80211_scan_state*) ; 
 int /*<<< orphan*/  ieee80211_draintask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_signal (struct ieee80211_scan_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_scan_state*) ; 
 int /*<<< orphan*/  taskqueue_drain_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ieee80211_swscan_detach(struct ieee80211com *ic)
{
	struct ieee80211_scan_state *ss = ic->ic_scan;

	if (ss != NULL) {
		scan_signal(ss, ISCAN_ABORT);
		ieee80211_draintask(ic, &SCAN_PRIVATE(ss)->ss_scan_start);
		taskqueue_drain_timeout(ic->ic_tq,
		    &SCAN_PRIVATE(ss)->ss_scan_curchan);
		KASSERT((ic->ic_flags & IEEE80211_F_SCAN) == 0,
		    ("scan still running"));

		/*
		 * For now, do the ss_ops detach here rather
		 * than ieee80211_scan_detach().
		 *
		 * I'll figure out how to cleanly split things up
		 * at a later date.
		 */
		if (ss->ss_ops != NULL) {
			ss->ss_ops->scan_detach(ss);
			ss->ss_ops = NULL;
		}
		ic->ic_scan = NULL;
		IEEE80211_FREE(SCAN_PRIVATE(ss), M_80211_SCAN);
	}
}