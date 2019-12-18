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
struct TYPE_2__ {struct ieee80211com* ss_ic; } ;
struct scan_state {TYPE_1__ base; int /*<<< orphan*/  ss_scan_curchan; int /*<<< orphan*/  ss_scan_start; } ;
struct ieee80211com {int /*<<< orphan*/  ic_scan_mindwell; int /*<<< orphan*/  ic_scan_curchan; TYPE_1__* ic_scan; int /*<<< orphan*/  ic_tq; int /*<<< orphan*/ * ic_scan_methods; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int IEEE80211_M_NOWAIT ; 
 int IEEE80211_M_ZERO ; 
 int /*<<< orphan*/  M_80211_SCAN ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scan_state*) ; 
 int /*<<< orphan*/  TIMEOUT_TASK_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scan_state*) ; 
 int /*<<< orphan*/  scan_curchan ; 
 int /*<<< orphan*/  scan_curchan_task ; 
 int /*<<< orphan*/  scan_mindwell ; 
 int /*<<< orphan*/  scan_start ; 
 int /*<<< orphan*/  swscan_methods ; 

void
ieee80211_swscan_attach(struct ieee80211com *ic)
{
	struct scan_state *ss;

	/*
	 * Setup the default methods
	 */
	ic->ic_scan_methods = &swscan_methods;

	/* Allocate initial scan state */
	ss = (struct scan_state *) IEEE80211_MALLOC(sizeof(struct scan_state),
		M_80211_SCAN, IEEE80211_M_NOWAIT | IEEE80211_M_ZERO);
	if (ss == NULL) {
		ic->ic_scan = NULL;
		return;
	}
	TASK_INIT(&ss->ss_scan_start, 0, scan_start, ss);
	TIMEOUT_TASK_INIT(ic->ic_tq, &ss->ss_scan_curchan, 0,
	    scan_curchan_task, ss);

	ic->ic_scan = &ss->base;
	ss->base.ss_ic = ic;

	ic->ic_scan_curchan = scan_curchan;
	ic->ic_scan_mindwell = scan_mindwell;
}