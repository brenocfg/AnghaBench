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
struct ieee80211_node_table {scalar_t__ nt_count; int /*<<< orphan*/  nt_node; } ;
struct ieee80211_node {int /*<<< orphan*/ * ni_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_NODE_LOCK_ASSERT (struct ieee80211_node_table*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct ieee80211_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ieee80211_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_hash ; 
 int /*<<< orphan*/  ni_list ; 

__attribute__((used)) static void
ieee80211_del_node_nt(struct ieee80211_node_table *nt,
    struct ieee80211_node *ni)
{

	IEEE80211_NODE_LOCK_ASSERT(nt);

	TAILQ_REMOVE(&nt->nt_node, ni, ni_list);
	LIST_REMOVE(ni, ni_hash);
	nt->nt_count--;
	KASSERT(nt->nt_count >= 0,
	    ("nt_count is negative (%d)!\n", nt->nt_count));
	ni->ni_table = NULL;
}