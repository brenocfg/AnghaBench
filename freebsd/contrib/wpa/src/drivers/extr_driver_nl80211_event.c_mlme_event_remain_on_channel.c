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
struct TYPE_2__ {unsigned int freq; unsigned int duration; } ;
union wpa_event_data {TYPE_1__ remain_on_channel; } ;
typedef  scalar_t__ u64 ;
struct wpa_driver_nl80211_data {scalar_t__ remain_on_chan_cookie; int /*<<< orphan*/  ctx; scalar_t__ pending_remain_on_chan; } ;
struct nlattr {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_CANCEL_REMAIN_ON_CHANNEL ; 
 int /*<<< orphan*/  EVENT_REMAIN_ON_CHANNEL ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t NL80211_ATTR_COOKIE ; 
 size_t NL80211_ATTR_DURATION ; 
 size_t NL80211_ATTR_WIPHY_CHANNEL_TYPE ; 
 size_t NL80211_ATTR_WIPHY_FREQ ; 
 unsigned int nla_get_u32 (struct nlattr*) ; 
 scalar_t__ nla_get_u64 (struct nlattr*) ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,unsigned int,unsigned int,unsigned int,unsigned long long,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union wpa_event_data*) ; 

__attribute__((used)) static void mlme_event_remain_on_channel(struct wpa_driver_nl80211_data *drv,
					 int cancel_event, struct nlattr *tb[])
{
	unsigned int freq, chan_type, duration;
	union wpa_event_data data;
	u64 cookie;

	if (tb[NL80211_ATTR_WIPHY_FREQ])
		freq = nla_get_u32(tb[NL80211_ATTR_WIPHY_FREQ]);
	else
		freq = 0;

	if (tb[NL80211_ATTR_WIPHY_CHANNEL_TYPE])
		chan_type = nla_get_u32(tb[NL80211_ATTR_WIPHY_CHANNEL_TYPE]);
	else
		chan_type = 0;

	if (tb[NL80211_ATTR_DURATION])
		duration = nla_get_u32(tb[NL80211_ATTR_DURATION]);
	else
		duration = 0;

	if (tb[NL80211_ATTR_COOKIE])
		cookie = nla_get_u64(tb[NL80211_ATTR_COOKIE]);
	else
		cookie = 0;

	wpa_printf(MSG_DEBUG, "nl80211: Remain-on-channel event (cancel=%d "
		   "freq=%u channel_type=%u duration=%u cookie=0x%llx (%s))",
		   cancel_event, freq, chan_type, duration,
		   (long long unsigned int) cookie,
		   cookie == drv->remain_on_chan_cookie ? "match" : "unknown");

	if (cookie != drv->remain_on_chan_cookie)
		return; /* not for us */

	if (cancel_event)
		drv->pending_remain_on_chan = 0;

	os_memset(&data, 0, sizeof(data));
	data.remain_on_channel.freq = freq;
	data.remain_on_channel.duration = duration;
	wpa_supplicant_event(drv->ctx, cancel_event ?
			     EVENT_CANCEL_REMAIN_ON_CHANNEL :
			     EVENT_REMAIN_ON_CHANNEL, &data);
}