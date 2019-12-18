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
struct sta_info {struct mbo_non_pref_chan_info* non_pref_chan; } ;
struct mbo_non_pref_chan_info {struct mbo_non_pref_chan_info* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct mbo_non_pref_chan_info*) ; 

void mbo_ap_sta_free(struct sta_info *sta)
{
	struct mbo_non_pref_chan_info *info, *prev;

	info = sta->non_pref_chan;
	sta->non_pref_chan = NULL;
	while (info) {
		prev = info;
		info = info->next;
		os_free(prev);
	}
}