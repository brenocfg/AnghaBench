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
struct ieee80211com {int /*<<< orphan*/  ic_name; } ;
struct ieee80211_node_table {char const* nt_name; int nt_inact_init; int nt_keyixmax; struct ieee80211_node** nt_keyixmap; scalar_t__ nt_count; int /*<<< orphan*/  nt_node; struct ieee80211com* nt_ic; } ;
struct ieee80211_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int IEEE80211_M_NOWAIT ; 
 int IEEE80211_M_ZERO ; 
 int /*<<< orphan*/  IEEE80211_NODE_LOCK_INIT (struct ieee80211_node_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_80211_NODE ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ic_printf (struct ieee80211com*,char*,int) ; 

__attribute__((used)) static void
ieee80211_node_table_init(struct ieee80211com *ic,
	struct ieee80211_node_table *nt,
	const char *name, int inact, int keyixmax)
{

	nt->nt_ic = ic;
	IEEE80211_NODE_LOCK_INIT(nt, ic->ic_name);
	TAILQ_INIT(&nt->nt_node);
	nt->nt_count = 0;
	nt->nt_name = name;
	nt->nt_inact_init = inact;
	nt->nt_keyixmax = keyixmax;
	if (nt->nt_keyixmax > 0) {
		nt->nt_keyixmap = (struct ieee80211_node **) IEEE80211_MALLOC(
			keyixmax * sizeof(struct ieee80211_node *),
			M_80211_NODE,
			IEEE80211_M_NOWAIT | IEEE80211_M_ZERO);
		if (nt->nt_keyixmap == NULL)
			ic_printf(ic,
			    "Cannot allocate key index map with %u entries\n",
			    keyixmax);
	} else
		nt->nt_keyixmap = NULL;
}