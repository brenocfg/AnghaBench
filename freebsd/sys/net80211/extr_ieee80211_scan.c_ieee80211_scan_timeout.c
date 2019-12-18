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
struct ieee80211com {struct ieee80211_scan_state* ic_scan; } ;
struct ieee80211_scan_state {TYPE_1__* ss_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* scan_age ) (struct ieee80211_scan_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ieee80211_scan_state*) ; 

void
ieee80211_scan_timeout(struct ieee80211com *ic)
{
	struct ieee80211_scan_state *ss = ic->ic_scan;

	if (ss->ss_ops != NULL)
		ss->ss_ops->scan_age(ss);
}