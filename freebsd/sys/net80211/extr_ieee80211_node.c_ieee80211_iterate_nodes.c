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
 int /*<<< orphan*/  ieee80211_iterate_nodes_vap (struct ieee80211_node_table*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

void
ieee80211_iterate_nodes(struct ieee80211_node_table *nt,
	ieee80211_iter_func *f, void *arg)
{
	/* XXX no way to pass error to the caller. */
	(void) ieee80211_iterate_nodes_vap(nt, NULL, f, arg);
}