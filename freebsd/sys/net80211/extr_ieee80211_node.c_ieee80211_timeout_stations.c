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
struct ieee80211_node_table {int dummy; } ;
struct ieee80211com {struct ieee80211_node_table ic_sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_iterate_nodes (struct ieee80211_node_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout_stations ; 

__attribute__((used)) static void
ieee80211_timeout_stations(struct ieee80211com *ic)
{
	struct ieee80211_node_table *nt = &ic->ic_sta;

	ieee80211_iterate_nodes(nt, timeout_stations, NULL);
}