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
struct sta_table {int dummy; } ;
struct ieee80211_scan_state {struct sta_table* ss_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FREE (struct sta_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_SCAN_ITER_LOCK_DESTROY (struct sta_table*) ; 
 int /*<<< orphan*/  IEEE80211_SCAN_TABLE_LOCK_DESTROY (struct sta_table*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_80211_SCAN ; 
 scalar_t__ nrefs ; 
 int /*<<< orphan*/  sta_flush_table (struct sta_table*) ; 

__attribute__((used)) static int
sta_detach(struct ieee80211_scan_state *ss)
{
	struct sta_table *st = ss->ss_priv;

	if (st != NULL) {
		sta_flush_table(st);
		IEEE80211_SCAN_TABLE_LOCK_DESTROY(st);
		IEEE80211_SCAN_ITER_LOCK_DESTROY(st);
		IEEE80211_FREE(st, M_80211_SCAN);
		KASSERT(nrefs > 0, ("imbalanced attach/detach"));
		nrefs--;		/* NB: we assume caller locking */
	}
	return 1;
}