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
struct TYPE_2__ {int unicast; int /*<<< orphan*/  src; } ;
union wpa_event_data {TYPE_1__ michael_mic_failure; } ;
typedef  int u8 ;
struct nlattr {int dummy; } ;
struct i802_bss {int /*<<< orphan*/  ctx; } ;
typedef  enum nl80211_key_type { ____Placeholder_nl80211_key_type } nl80211_key_type ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_MICHAEL_MIC_FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t NL80211_ATTR_KEY_IDX ; 
 size_t NL80211_ATTR_KEY_SEQ ; 
 size_t NL80211_ATTR_KEY_TYPE ; 
 size_t NL80211_ATTR_MAC ; 
 int NL80211_KEYTYPE_PAIRWISE ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int nla_get_u32 (struct nlattr*) ; 
 int nla_get_u8 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 int /*<<< orphan*/  os_memset (union wpa_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_supplicant_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union wpa_event_data*) ; 

__attribute__((used)) static void mlme_event_michael_mic_failure(struct i802_bss *bss,
					   struct nlattr *tb[])
{
	union wpa_event_data data;

	wpa_printf(MSG_DEBUG, "nl80211: MLME event Michael MIC failure");
	os_memset(&data, 0, sizeof(data));
	if (tb[NL80211_ATTR_MAC]) {
		wpa_hexdump(MSG_DEBUG, "nl80211: Source MAC address",
			    nla_data(tb[NL80211_ATTR_MAC]),
			    nla_len(tb[NL80211_ATTR_MAC]));
		data.michael_mic_failure.src = nla_data(tb[NL80211_ATTR_MAC]);
	}
	if (tb[NL80211_ATTR_KEY_SEQ]) {
		wpa_hexdump(MSG_DEBUG, "nl80211: TSC",
			    nla_data(tb[NL80211_ATTR_KEY_SEQ]),
			    nla_len(tb[NL80211_ATTR_KEY_SEQ]));
	}
	if (tb[NL80211_ATTR_KEY_TYPE]) {
		enum nl80211_key_type key_type =
			nla_get_u32(tb[NL80211_ATTR_KEY_TYPE]);
		wpa_printf(MSG_DEBUG, "nl80211: Key Type %d", key_type);
		if (key_type == NL80211_KEYTYPE_PAIRWISE)
			data.michael_mic_failure.unicast = 1;
	} else
		data.michael_mic_failure.unicast = 1;

	if (tb[NL80211_ATTR_KEY_IDX]) {
		u8 key_id = nla_get_u8(tb[NL80211_ATTR_KEY_IDX]);
		wpa_printf(MSG_DEBUG, "nl80211: Key Id %d", key_id);
	}

	wpa_supplicant_event(bss->ctx, EVENT_MICHAEL_MIC_FAILURE, &data);
}