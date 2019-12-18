#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct wpa_driver_nl80211_data {int dummy; } ;
struct phy_info_arg {int* num_modes; int last_mode; TYPE_1__* modes; int /*<<< orphan*/  dfs_domain; scalar_t__ failed; } ;
struct nl_msg {int dummy; } ;
struct i802_bss {struct wpa_driver_nl80211_data* drv; } ;
struct hostapd_hw_modes {int dummy; } ;
struct TYPE_3__ {struct TYPE_3__* rates; struct TYPE_3__* channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_ATTR_SPLIT_WIPHY_DUMP ; 
 int /*<<< orphan*/  NL80211_CMD_GET_WIPHY ; 
 int NL80211_PROTOCOL_FEATURE_SPLIT_WIPHY_DUMP ; 
 int NLM_F_DUMP ; 
 int get_nl80211_protocol_features (struct wpa_driver_nl80211_data*) ; 
 struct nl_msg* nl80211_cmd_msg (struct i802_bss*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl80211_dump_chan_list (struct hostapd_hw_modes*,int) ; 
 int /*<<< orphan*/  nl80211_set_regulatory_flags (struct wpa_driver_nl80211_data*,struct phy_info_arg*) ; 
 scalar_t__ nla_put_flag (struct nl_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct nl_msg*) ; 
 int /*<<< orphan*/  os_free (TYPE_1__*) ; 
 int /*<<< orphan*/  phy_info_handler ; 
 scalar_t__ send_and_recv_msgs (struct wpa_driver_nl80211_data*,struct nl_msg*,int /*<<< orphan*/ ,struct phy_info_arg*) ; 
 struct hostapd_hw_modes* wpa_driver_nl80211_postprocess_modes (TYPE_1__*,int*) ; 

struct hostapd_hw_modes *
nl80211_get_hw_feature_data(void *priv, u16 *num_modes, u16 *flags,
			    u8 *dfs_domain)
{
	u32 feat;
	struct i802_bss *bss = priv;
	struct wpa_driver_nl80211_data *drv = bss->drv;
	int nl_flags = 0;
	struct nl_msg *msg;
	struct phy_info_arg result = {
		.num_modes = num_modes,
		.modes = NULL,
		.last_mode = -1,
		.failed = 0,
		.dfs_domain = 0,
	};

	*num_modes = 0;
	*flags = 0;
	*dfs_domain = 0;

	feat = get_nl80211_protocol_features(drv);
	if (feat & NL80211_PROTOCOL_FEATURE_SPLIT_WIPHY_DUMP)
		nl_flags = NLM_F_DUMP;
	if (!(msg = nl80211_cmd_msg(bss, nl_flags, NL80211_CMD_GET_WIPHY)) ||
	    nla_put_flag(msg, NL80211_ATTR_SPLIT_WIPHY_DUMP)) {
		nlmsg_free(msg);
		return NULL;
	}

	if (send_and_recv_msgs(drv, msg, phy_info_handler, &result) == 0) {
		struct hostapd_hw_modes *modes;

		nl80211_set_regulatory_flags(drv, &result);
		if (result.failed) {
			int i;

			for (i = 0; result.modes && i < *num_modes; i++) {
				os_free(result.modes[i].channels);
				os_free(result.modes[i].rates);
			}
			os_free(result.modes);
			*num_modes = 0;
			return NULL;
		}

		*dfs_domain = result.dfs_domain;

		modes = wpa_driver_nl80211_postprocess_modes(result.modes,
							     num_modes);
		nl80211_dump_chan_list(modes, *num_modes);
		return modes;
	}

	return NULL;
}