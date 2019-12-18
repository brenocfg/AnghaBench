#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  initiator; } ;
union wpa_event_data {TYPE_1__ channel_list_changed; } ;
struct wpa_driver_nl80211_data {int /*<<< orphan*/  ctx; } ;
struct nlattr {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_CHANNEL_LIST_CHANGED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t NL80211_ATTR_FREQ_AFTER ; 
 size_t NL80211_ATTR_FREQ_BEFORE ; 
 int /*<<< orphan*/  REGDOM_BEACON_HINT ; 
 int /*<<< orphan*/  nl80211_dump_freq (char*,struct nlattr*) ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union wpa_event_data*) ; 

__attribute__((used)) static void nl80211_reg_beacon_hint_event(struct wpa_driver_nl80211_data *drv,
					   struct nlattr *tb[])
{
	union wpa_event_data data;

	wpa_printf(MSG_DEBUG, "nl80211: Regulatory beacon hint");
	os_memset(&data, 0, sizeof(data));
	data.channel_list_changed.initiator = REGDOM_BEACON_HINT;

	if (tb[NL80211_ATTR_FREQ_BEFORE])
		nl80211_dump_freq("before", tb[NL80211_ATTR_FREQ_BEFORE]);
	if (tb[NL80211_ATTR_FREQ_AFTER])
		nl80211_dump_freq("after", tb[NL80211_ATTR_FREQ_AFTER]);

	wpa_supplicant_event(drv->ctx, EVENT_CHANNEL_LIST_CHANGED, &data);
}