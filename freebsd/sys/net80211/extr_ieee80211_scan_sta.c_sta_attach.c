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
struct sta_table {int /*<<< orphan*/  st_entry; } ;
struct ieee80211_scan_state {struct sta_table* ss_priv; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int IEEE80211_M_NOWAIT ; 
 int IEEE80211_M_ZERO ; 
 int /*<<< orphan*/  IEEE80211_SCAN_ITER_LOCK_INIT (struct sta_table*,char*) ; 
 int /*<<< orphan*/  IEEE80211_SCAN_TABLE_LOCK_INIT (struct sta_table*,char*) ; 
 int /*<<< orphan*/  M_80211_SCAN ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nrefs ; 

__attribute__((used)) static int
sta_attach(struct ieee80211_scan_state *ss)
{
	struct sta_table *st;

	st = (struct sta_table *) IEEE80211_MALLOC(sizeof(struct sta_table),
		M_80211_SCAN,
		IEEE80211_M_NOWAIT | IEEE80211_M_ZERO);
	if (st == NULL)
		return 0;
	IEEE80211_SCAN_TABLE_LOCK_INIT(st, "scantable");
	IEEE80211_SCAN_ITER_LOCK_INIT(st, "scangen");
	TAILQ_INIT(&st->st_entry);
	ss->ss_priv = st;
	nrefs++;			/* NB: we assume caller locking */
	return 1;
}