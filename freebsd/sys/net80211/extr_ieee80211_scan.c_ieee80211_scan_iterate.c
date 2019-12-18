#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211vap {TYPE_1__* iv_ic; } ;
struct ieee80211_scan_state {TYPE_2__* ss_ops; } ;
typedef  int /*<<< orphan*/  ieee80211_scan_iter_func ;
struct TYPE_4__ {int /*<<< orphan*/  (* scan_iterate ) (struct ieee80211_scan_state*,int /*<<< orphan*/ *,void*) ;} ;
struct TYPE_3__ {struct ieee80211_scan_state* ic_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ieee80211_scan_state*,int /*<<< orphan*/ *,void*) ; 

void
ieee80211_scan_iterate(struct ieee80211vap *vap,
	ieee80211_scan_iter_func *f, void *arg)
{
	struct ieee80211_scan_state *ss = vap->iv_ic->ic_scan;

	if (ss->ss_ops != NULL)
		ss->ss_ops->scan_iterate(ss, f, arg);
}