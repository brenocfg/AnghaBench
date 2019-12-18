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
struct ieee80211com {int /*<<< orphan*/  ic_stageq; int /*<<< orphan*/  ic_sta; int /*<<< orphan*/  ic_inact; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ageq_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ageq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_node_table_cleanup (int /*<<< orphan*/ *) ; 

void
ieee80211_node_detach(struct ieee80211com *ic)
{

	callout_drain(&ic->ic_inact);
	ieee80211_node_table_cleanup(&ic->ic_sta);
	ieee80211_ageq_drain(&ic->ic_stageq);
	ieee80211_ageq_cleanup(&ic->ic_stageq);
}