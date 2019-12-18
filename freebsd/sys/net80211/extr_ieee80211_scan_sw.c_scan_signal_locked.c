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
struct timeout_task {int dummy; } ;
struct scan_state {int ss_iflags; struct timeout_task ss_scan_curchan; } ;
struct ieee80211com {int /*<<< orphan*/  ic_tq; } ;
struct ieee80211_scan_state {struct ieee80211com* ss_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LOCK_ASSERT (struct ieee80211com*) ; 
 int ISCAN_RUNNING ; 
 struct scan_state* SCAN_PRIVATE (struct ieee80211_scan_state*) ; 
 scalar_t__ taskqueue_cancel_timeout (int /*<<< orphan*/ ,struct timeout_task*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue_timeout (int /*<<< orphan*/ ,struct timeout_task*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
scan_signal_locked(struct ieee80211_scan_state *ss, int iflags)
{
	struct scan_state *ss_priv = SCAN_PRIVATE(ss);
	struct timeout_task *scan_task = &ss_priv->ss_scan_curchan;
	struct ieee80211com *ic = ss->ss_ic;

	IEEE80211_LOCK_ASSERT(ic);

	ss_priv->ss_iflags |= iflags;
	if (ss_priv->ss_iflags & ISCAN_RUNNING) {
		if (taskqueue_cancel_timeout(ic->ic_tq, scan_task, NULL) == 0)
			taskqueue_enqueue_timeout(ic->ic_tq, scan_task, 0);
	}
}