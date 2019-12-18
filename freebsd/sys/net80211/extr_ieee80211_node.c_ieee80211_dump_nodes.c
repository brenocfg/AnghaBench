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
typedef  int /*<<< orphan*/  ieee80211_iter_func ;

/* Variables and functions */
 scalar_t__ ieee80211_dump_node ; 
 int /*<<< orphan*/  ieee80211_iterate_nodes (struct ieee80211_node_table*,int /*<<< orphan*/ *,struct ieee80211_node_table*) ; 

void
ieee80211_dump_nodes(struct ieee80211_node_table *nt)
{
	ieee80211_iterate_nodes(nt,
		(ieee80211_iter_func *) ieee80211_dump_node, nt);
}