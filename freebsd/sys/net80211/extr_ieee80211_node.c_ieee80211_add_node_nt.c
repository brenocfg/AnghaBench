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
struct ieee80211com {int dummy; } ;
struct ieee80211_node_table {int /*<<< orphan*/  nt_count; int /*<<< orphan*/ * nt_hash; int /*<<< orphan*/  nt_node; struct ieee80211com* nt_ic; } ;
struct ieee80211_node {struct ieee80211_node_table* ni_table; int /*<<< orphan*/  ni_macaddr; } ;

/* Variables and functions */
 int IEEE80211_NODE_HASH (struct ieee80211com*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_NODE_LOCK_ASSERT (struct ieee80211_node_table*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ieee80211_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ieee80211_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_hash ; 
 int /*<<< orphan*/  ni_list ; 

__attribute__((used)) static void
ieee80211_add_node_nt(struct ieee80211_node_table *nt,
    struct ieee80211_node *ni)
{
	struct ieee80211com *ic = nt->nt_ic;
	int hash;

	IEEE80211_NODE_LOCK_ASSERT(nt);

	hash = IEEE80211_NODE_HASH(ic, ni->ni_macaddr);
	(void) ic;	/* XXX IEEE80211_NODE_HASH */
	TAILQ_INSERT_TAIL(&nt->nt_node, ni, ni_list);
	LIST_INSERT_HEAD(&nt->nt_hash[hash], ni, ni_hash);
	nt->nt_count++;
	ni->ni_table = nt;
}