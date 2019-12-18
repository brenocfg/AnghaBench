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
struct ieee80211_dfs_state {int /*<<< orphan*/  cac_timer; int /*<<< orphan*/  nol_timer; } ;
struct ieee80211com {int /*<<< orphan*/  ic_set_quiet; struct ieee80211_dfs_state ic_dfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LOCK_OBJ (struct ieee80211com*) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_set_quiet ; 

void
ieee80211_dfs_attach(struct ieee80211com *ic)
{
	struct ieee80211_dfs_state *dfs = &ic->ic_dfs;

	callout_init_mtx(&dfs->nol_timer, IEEE80211_LOCK_OBJ(ic), 0);
	callout_init_mtx(&dfs->cac_timer, IEEE80211_LOCK_OBJ(ic), 0);

	ic->ic_set_quiet = null_set_quiet;
}