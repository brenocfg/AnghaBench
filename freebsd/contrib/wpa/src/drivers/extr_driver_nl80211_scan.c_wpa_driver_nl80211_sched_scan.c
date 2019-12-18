#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wpa_driver_scan_params {scalar_t__ sched_scan_plans_num; int filter_rssi; int relative_rssi; int relative_adjust_band; int sched_scan_start_delay; scalar_t__ relative_adjust_rssi; scalar_t__ relative_rssi_set; TYPE_1__* sched_scan_plans; } ;
struct TYPE_5__ {scalar_t__ max_sched_scan_plans; int max_match_sets; scalar_t__ max_sched_scan_plan_iterations; int /*<<< orphan*/  sched_scan_supported; } ;
struct wpa_driver_nl80211_data {size_t num_filter_ssids; TYPE_3__* filter_ssids; TYPE_2__ capa; int /*<<< orphan*/  ctx; } ;
struct nlattr {int dummy; } ;
struct nl_msg {int dummy; } ;
struct nl80211_bss_select_rssi_adjust {scalar_t__ delta; int /*<<< orphan*/  band; } ;
struct i802_bss {struct wpa_driver_nl80211_data* drv; } ;
typedef  int /*<<< orphan*/  rssi_adjust ;
struct TYPE_6__ {int ssid_len; struct nl80211_bss_select_rssi_adjust* ssid; } ;
struct TYPE_4__ {int interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  NL80211_ATTR_SCHED_SCAN_DELAY ; 
 int /*<<< orphan*/  NL80211_ATTR_SCHED_SCAN_INTERVAL ; 
 size_t NL80211_ATTR_SCHED_SCAN_MATCH ; 
 int /*<<< orphan*/  NL80211_ATTR_SCHED_SCAN_MATCH_SSID ; 
 int /*<<< orphan*/  NL80211_ATTR_SCHED_SCAN_RELATIVE_RSSI ; 
 int /*<<< orphan*/  NL80211_ATTR_SCHED_SCAN_RSSI_ADJUST ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  NL80211_CMD_START_SCHED_SCAN ; 
 int /*<<< orphan*/  NL80211_SCHED_SCAN_MATCH_ATTR_RSSI ; 
#define  WPA_SETBAND_2G 129 
#define  WPA_SETBAND_5G 128 
 int android_pno_start (struct i802_bss*,struct wpa_driver_scan_params*) ; 
 struct nl_msg* nl80211_scan_common (struct i802_bss*,int /*<<< orphan*/ ,struct wpa_driver_scan_params*) ; 
 scalar_t__ nl80211_sched_scan_add_scan_plans (struct wpa_driver_nl80211_data*,struct nl_msg*,struct wpa_driver_scan_params*) ; 
 int /*<<< orphan*/  nla_nest_end (struct nl_msg*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct nl_msg*,size_t) ; 
 scalar_t__ nla_put (struct nl_msg*,int /*<<< orphan*/ ,int,struct nl80211_bss_select_rssi_adjust*) ; 
 scalar_t__ nla_put_u32 (struct nl_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlmsg_free (struct nl_msg*) ; 
 int /*<<< orphan*/  os_memset (struct nl80211_bss_select_rssi_adjust*,int /*<<< orphan*/ ,int) ; 
 int send_and_recv_msgs (struct wpa_driver_nl80211_data*,struct nl_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  wpa_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int wpa_ssid_txt (struct nl80211_bss_select_rssi_adjust*,int) ; 

int wpa_driver_nl80211_sched_scan(void *priv,
				  struct wpa_driver_scan_params *params)
{
	struct i802_bss *bss = priv;
	struct wpa_driver_nl80211_data *drv = bss->drv;
	int ret = -1;
	struct nl_msg *msg;
	size_t i;

	wpa_dbg(drv->ctx, MSG_DEBUG, "nl80211: sched_scan request");

#ifdef ANDROID
	if (!drv->capa.sched_scan_supported)
		return android_pno_start(bss, params);
#endif /* ANDROID */

	if (!params->sched_scan_plans_num ||
	    params->sched_scan_plans_num > drv->capa.max_sched_scan_plans) {
		wpa_printf(MSG_ERROR,
			   "nl80211: Invalid number of sched scan plans: %u",
			   params->sched_scan_plans_num);
		return -1;
	}

	msg = nl80211_scan_common(bss, NL80211_CMD_START_SCHED_SCAN, params);
	if (!msg)
		goto fail;

	if (drv->capa.max_sched_scan_plan_iterations) {
		if (nl80211_sched_scan_add_scan_plans(drv, msg, params))
			goto fail;
	} else {
		if (nla_put_u32(msg, NL80211_ATTR_SCHED_SCAN_INTERVAL,
				params->sched_scan_plans[0].interval * 1000))
			goto fail;
	}

	if ((drv->num_filter_ssids &&
	    (int) drv->num_filter_ssids <= drv->capa.max_match_sets) ||
	    params->filter_rssi) {
		struct nlattr *match_sets;
		match_sets = nla_nest_start(msg, NL80211_ATTR_SCHED_SCAN_MATCH);
		if (match_sets == NULL)
			goto fail;

		for (i = 0; i < drv->num_filter_ssids; i++) {
			struct nlattr *match_set_ssid;
			wpa_printf(MSG_MSGDUMP,
				   "nl80211: Sched scan filter SSID %s",
				   wpa_ssid_txt(drv->filter_ssids[i].ssid,
						drv->filter_ssids[i].ssid_len));

			match_set_ssid = nla_nest_start(msg, i + 1);
			if (match_set_ssid == NULL ||
			    nla_put(msg, NL80211_ATTR_SCHED_SCAN_MATCH_SSID,
				    drv->filter_ssids[i].ssid_len,
				    drv->filter_ssids[i].ssid) ||
			    (params->filter_rssi &&
			     nla_put_u32(msg,
					 NL80211_SCHED_SCAN_MATCH_ATTR_RSSI,
					 params->filter_rssi)))
				goto fail;

			nla_nest_end(msg, match_set_ssid);
		}

		/*
		 * Due to backward compatibility code, newer kernels treat this
		 * matchset (with only an RSSI filter) as the default for all
		 * other matchsets, unless it's the only one, in which case the
		 * matchset will actually allow all SSIDs above the RSSI.
		 */
		if (params->filter_rssi) {
			struct nlattr *match_set_rssi;
			match_set_rssi = nla_nest_start(msg, 0);
			if (match_set_rssi == NULL ||
			    nla_put_u32(msg, NL80211_SCHED_SCAN_MATCH_ATTR_RSSI,
					params->filter_rssi))
				goto fail;
			wpa_printf(MSG_MSGDUMP,
				   "nl80211: Sched scan RSSI filter %d dBm",
				   params->filter_rssi);
			nla_nest_end(msg, match_set_rssi);
		}

		nla_nest_end(msg, match_sets);
	}

	if (params->relative_rssi_set) {
		struct nl80211_bss_select_rssi_adjust rssi_adjust;

		os_memset(&rssi_adjust, 0, sizeof(rssi_adjust));
		wpa_printf(MSG_DEBUG, "nl80211: Relative RSSI: %d",
			   params->relative_rssi);
		if (nla_put_u32(msg, NL80211_ATTR_SCHED_SCAN_RELATIVE_RSSI,
				params->relative_rssi))
			goto fail;

		if (params->relative_adjust_rssi) {
			int pref_band_set = 1;

			switch (params->relative_adjust_band) {
			case WPA_SETBAND_5G:
				rssi_adjust.band = NL80211_BAND_5GHZ;
				break;
			case WPA_SETBAND_2G:
				rssi_adjust.band = NL80211_BAND_2GHZ;
				break;
			default:
				pref_band_set = 0;
				break;
			}
			rssi_adjust.delta = params->relative_adjust_rssi;

			if (pref_band_set &&
			    nla_put(msg, NL80211_ATTR_SCHED_SCAN_RSSI_ADJUST,
				    sizeof(rssi_adjust), &rssi_adjust))
				goto fail;
		}
	}

	if (params->sched_scan_start_delay &&
	    nla_put_u32(msg, NL80211_ATTR_SCHED_SCAN_DELAY,
			params->sched_scan_start_delay))
		goto fail;

	ret = send_and_recv_msgs(drv, msg, NULL, NULL);

	/* TODO: if we get an error here, we should fall back to normal scan */

	msg = NULL;
	if (ret) {
		wpa_printf(MSG_DEBUG, "nl80211: Sched scan start failed: "
			   "ret=%d (%s)", ret, strerror(-ret));
		goto fail;
	}

	wpa_printf(MSG_DEBUG, "nl80211: Sched scan requested (ret=%d)", ret);

fail:
	nlmsg_free(msg);
	return ret;
}