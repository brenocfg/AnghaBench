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
typedef  int u32 ;
struct TYPE_2__ {int flags; int num_multichan_concurrent; int max_remain_on_chan; int max_csa_counters; int max_sched_scan_plans; scalar_t__ max_sched_scan_plan_iterations; int /*<<< orphan*/  max_sched_scan_plan_interval; int /*<<< orphan*/  mac_addr_rand_scan_supported; int /*<<< orphan*/  mac_addr_rand_sched_scan_supported; int /*<<< orphan*/  wmm_ac_supported; } ;
struct wpa_driver_nl80211_data {TYPE_1__ capa; int /*<<< orphan*/  first_bss; } ;
struct wiphy_info_data {int error; int num_multichan_concurrent; scalar_t__ channel_switch_supported; int /*<<< orphan*/  mac_addr_rand_scan_supported; int /*<<< orphan*/  mac_addr_rand_sched_scan_supported; int /*<<< orphan*/  wmm_ac_supported; scalar_t__ p2p_concurrent; scalar_t__ p2p_client_supported; scalar_t__ p2p_go_supported; int /*<<< orphan*/  connect_supported; scalar_t__ auth_supported; struct wpa_driver_nl80211_data* drv; TYPE_1__* capa; } ;
struct nl_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  NL80211_ATTR_SPLIT_WIPHY_DUMP ; 
 int /*<<< orphan*/  NL80211_CMD_GET_WIPHY ; 
 int NL80211_PROTOCOL_FEATURE_SPLIT_WIPHY_DUMP ; 
 int NLM_F_DUMP ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int WPA_DRIVER_FLAGS_AP_CSA ; 
 int WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE ; 
 int WPA_DRIVER_FLAGS_P2P_CAPABLE ; 
 int WPA_DRIVER_FLAGS_P2P_CONCURRENT ; 
 int WPA_DRIVER_FLAGS_P2P_MGMT_AND_NON_P2P ; 
 int WPA_DRIVER_FLAGS_SME ; 
 int get_nl80211_protocol_features (struct wpa_driver_nl80211_data*) ; 
 struct nl_msg* nl80211_cmd_msg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct nl_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct nl_msg*) ; 
 int /*<<< orphan*/  os_memset (struct wiphy_info_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ send_and_recv_msgs (struct wpa_driver_nl80211_data*,struct nl_msg*,int /*<<< orphan*/ ,struct wiphy_info_data*) ; 
 int /*<<< orphan*/  wiphy_info_handler ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wpa_driver_nl80211_get_info(struct wpa_driver_nl80211_data *drv,
				       struct wiphy_info_data *info)
{
	u32 feat;
	struct nl_msg *msg;
	int flags = 0;

	os_memset(info, 0, sizeof(*info));
	info->capa = &drv->capa;
	info->drv = drv;

	feat = get_nl80211_protocol_features(drv);
	if (feat & NL80211_PROTOCOL_FEATURE_SPLIT_WIPHY_DUMP)
		flags = NLM_F_DUMP;
	msg = nl80211_cmd_msg(drv->first_bss, flags, NL80211_CMD_GET_WIPHY);
	if (!msg || nla_put_flag(msg, NL80211_ATTR_SPLIT_WIPHY_DUMP)) {
		nlmsg_free(msg);
		return -1;
	}

	if (send_and_recv_msgs(drv, msg, wiphy_info_handler, info))
		return -1;

	if (info->auth_supported)
		drv->capa.flags |= WPA_DRIVER_FLAGS_SME;
	else if (!info->connect_supported) {
		wpa_printf(MSG_INFO, "nl80211: Driver does not support "
			   "authentication/association or connect commands");
		info->error = 1;
	}

	if (info->p2p_go_supported && info->p2p_client_supported)
		drv->capa.flags |= WPA_DRIVER_FLAGS_P2P_CAPABLE;
	if (info->p2p_concurrent) {
		wpa_printf(MSG_DEBUG, "nl80211: Use separate P2P group "
			   "interface (driver advertised support)");
		drv->capa.flags |= WPA_DRIVER_FLAGS_P2P_CONCURRENT;
		drv->capa.flags |= WPA_DRIVER_FLAGS_P2P_MGMT_AND_NON_P2P;
	}
	if (info->num_multichan_concurrent > 1) {
		wpa_printf(MSG_DEBUG, "nl80211: Enable multi-channel "
			   "concurrent (driver advertised support)");
		drv->capa.num_multichan_concurrent =
			info->num_multichan_concurrent;
	}
	if (drv->capa.flags & WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE)
		wpa_printf(MSG_DEBUG, "nl80211: use P2P_DEVICE support");

	/* default to 5000 since early versions of mac80211 don't set it */
	if (!drv->capa.max_remain_on_chan)
		drv->capa.max_remain_on_chan = 5000;

	drv->capa.wmm_ac_supported = info->wmm_ac_supported;

	drv->capa.mac_addr_rand_sched_scan_supported =
		info->mac_addr_rand_sched_scan_supported;
	drv->capa.mac_addr_rand_scan_supported =
		info->mac_addr_rand_scan_supported;

	if (info->channel_switch_supported) {
		drv->capa.flags |= WPA_DRIVER_FLAGS_AP_CSA;
		if (!drv->capa.max_csa_counters)
			drv->capa.max_csa_counters = 1;
	}

	if (!drv->capa.max_sched_scan_plans) {
		drv->capa.max_sched_scan_plans = 1;
		drv->capa.max_sched_scan_plan_interval = UINT32_MAX;
		drv->capa.max_sched_scan_plan_iterations = 0;
	}

	return 0;
}