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
struct ieee80211com {int /*<<< orphan*/  ic_tq; int /*<<< orphan*/  ic_chw_task; int /*<<< orphan*/  ic_bmiss_task; int /*<<< orphan*/  ic_chan_task; int /*<<< orphan*/  ic_promisc_task; int /*<<< orphan*/  ic_mcast_task; int /*<<< orphan*/  ic_parent_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_draintask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_unblock (int /*<<< orphan*/ ) ; 

void
ieee80211_waitfor_parent(struct ieee80211com *ic)
{
	taskqueue_block(ic->ic_tq);
	ieee80211_draintask(ic, &ic->ic_parent_task);
	ieee80211_draintask(ic, &ic->ic_mcast_task);
	ieee80211_draintask(ic, &ic->ic_promisc_task);
	ieee80211_draintask(ic, &ic->ic_chan_task);
	ieee80211_draintask(ic, &ic->ic_bmiss_task);
	ieee80211_draintask(ic, &ic->ic_chw_task);
	taskqueue_unblock(ic->ic_tq);
}