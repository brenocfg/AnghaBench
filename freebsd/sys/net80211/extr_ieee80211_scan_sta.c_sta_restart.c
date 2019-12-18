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
struct sta_table {int st_newscan; } ;
struct ieee80211vap {int dummy; } ;
struct ieee80211_scan_state {struct sta_table* ss_priv; } ;

/* Variables and functions */

__attribute__((used)) static int
sta_restart(struct ieee80211_scan_state *ss, struct ieee80211vap *vap)
{
	struct sta_table *st = ss->ss_priv;

	st->st_newscan = 1;
	return 0;
}