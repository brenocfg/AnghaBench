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
struct sta_info {struct wpa_state_machine* wpa_sm; struct sta_info* next; } ;
struct hostapd_data {struct sta_info* sta_list; } ;

/* Variables and functions */

__attribute__((used)) static int hostapd_wpa_auth_for_each_sta(
	void *ctx, int (*cb)(struct wpa_state_machine *sm, void *ctx),
	void *cb_ctx)
{
	struct hostapd_data *hapd = ctx;
	struct sta_info *sta;

	for (sta = hapd->sta_list; sta; sta = sta->next) {
		if (sta->wpa_sm && cb(sta->wpa_sm, cb_ctx))
			return 1;
	}
	return 0;
}