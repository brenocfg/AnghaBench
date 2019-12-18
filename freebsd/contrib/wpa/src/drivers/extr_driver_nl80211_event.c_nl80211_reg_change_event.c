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
struct TYPE_2__ {int alpha2; int /*<<< orphan*/  type; int /*<<< orphan*/  initiator; } ;
union wpa_event_data {TYPE_1__ channel_list_changed; } ;
struct wpa_driver_nl80211_data {int /*<<< orphan*/  ctx; } ;
struct nlattr {int dummy; } ;
typedef  enum nl80211_reg_type { ____Placeholder_nl80211_reg_type } nl80211_reg_type ;
typedef  enum nl80211_reg_initiator { ____Placeholder_nl80211_reg_initiator } nl80211_reg_initiator ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_CHANNEL_LIST_CHANGED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t NL80211_ATTR_REG_ALPHA2 ; 
 size_t NL80211_ATTR_REG_INITIATOR ; 
 size_t NL80211_ATTR_REG_TYPE ; 
#define  NL80211_REGDOM_SET_BY_CORE 135 
#define  NL80211_REGDOM_SET_BY_COUNTRY_IE 134 
#define  NL80211_REGDOM_SET_BY_DRIVER 133 
#define  NL80211_REGDOM_SET_BY_USER 132 
#define  NL80211_REGDOM_TYPE_COUNTRY 131 
#define  NL80211_REGDOM_TYPE_CUSTOM_WORLD 130 
#define  NL80211_REGDOM_TYPE_INTERSECTION 129 
#define  NL80211_REGDOM_TYPE_WORLD 128 
 int /*<<< orphan*/  REGDOM_SET_BY_CORE ; 
 int /*<<< orphan*/  REGDOM_SET_BY_COUNTRY_IE ; 
 int /*<<< orphan*/  REGDOM_SET_BY_DRIVER ; 
 int /*<<< orphan*/  REGDOM_SET_BY_USER ; 
 int /*<<< orphan*/  REGDOM_TYPE_COUNTRY ; 
 int /*<<< orphan*/  REGDOM_TYPE_CUSTOM_WORLD ; 
 int /*<<< orphan*/  REGDOM_TYPE_INTERSECTION ; 
 int /*<<< orphan*/  REGDOM_TYPE_WORLD ; 
 int /*<<< orphan*/  nla_get_string (struct nlattr*) ; 
 int nla_get_u8 (struct nlattr*) ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_strlcpy (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_supplicant_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union wpa_event_data*) ; 

__attribute__((used)) static void nl80211_reg_change_event(struct wpa_driver_nl80211_data *drv,
				     struct nlattr *tb[])
{
	union wpa_event_data data;
	enum nl80211_reg_initiator init;

	wpa_printf(MSG_DEBUG, "nl80211: Regulatory domain change");

	if (tb[NL80211_ATTR_REG_INITIATOR] == NULL)
		return;

	os_memset(&data, 0, sizeof(data));
	init = nla_get_u8(tb[NL80211_ATTR_REG_INITIATOR]);
	wpa_printf(MSG_DEBUG, " * initiator=%d", init);
	switch (init) {
	case NL80211_REGDOM_SET_BY_CORE:
		data.channel_list_changed.initiator = REGDOM_SET_BY_CORE;
		break;
	case NL80211_REGDOM_SET_BY_USER:
		data.channel_list_changed.initiator = REGDOM_SET_BY_USER;
		break;
	case NL80211_REGDOM_SET_BY_DRIVER:
		data.channel_list_changed.initiator = REGDOM_SET_BY_DRIVER;
		break;
	case NL80211_REGDOM_SET_BY_COUNTRY_IE:
		data.channel_list_changed.initiator = REGDOM_SET_BY_COUNTRY_IE;
		break;
	}

	if (tb[NL80211_ATTR_REG_TYPE]) {
		enum nl80211_reg_type type;
		type = nla_get_u8(tb[NL80211_ATTR_REG_TYPE]);
		wpa_printf(MSG_DEBUG, " * type=%d", type);
		switch (type) {
		case NL80211_REGDOM_TYPE_COUNTRY:
			data.channel_list_changed.type = REGDOM_TYPE_COUNTRY;
			break;
		case NL80211_REGDOM_TYPE_WORLD:
			data.channel_list_changed.type = REGDOM_TYPE_WORLD;
			break;
		case NL80211_REGDOM_TYPE_CUSTOM_WORLD:
			data.channel_list_changed.type =
				REGDOM_TYPE_CUSTOM_WORLD;
			break;
		case NL80211_REGDOM_TYPE_INTERSECTION:
			data.channel_list_changed.type =
				REGDOM_TYPE_INTERSECTION;
			break;
		}
	}

	if (tb[NL80211_ATTR_REG_ALPHA2]) {
		os_strlcpy(data.channel_list_changed.alpha2,
			   nla_get_string(tb[NL80211_ATTR_REG_ALPHA2]),
			   sizeof(data.channel_list_changed.alpha2));
		wpa_printf(MSG_DEBUG, " * alpha2=%s",
			   data.channel_list_changed.alpha2);
	}

	wpa_supplicant_event(drv->ctx, EVENT_CHANNEL_LIST_CHANGED, &data);
}