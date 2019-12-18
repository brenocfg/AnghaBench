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
struct wpa_scan_results {size_t num; int /*<<< orphan*/ * res; } ;
struct wpa_driver_nl80211_data {int /*<<< orphan*/  first_bss; } ;
struct nl_msg {int dummy; } ;
struct nl80211_noise_info {int dummy; } ;
struct nl80211_bss_info_arg {struct wpa_scan_results* res; struct wpa_driver_nl80211_data* drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  NL80211_CMD_GET_SCAN ; 
 int /*<<< orphan*/  NLM_F_DUMP ; 
 int /*<<< orphan*/  bss_info_handler ; 
 struct nl_msg* nl80211_cmd_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nl80211_get_noise_for_scan_results (struct wpa_driver_nl80211_data*,struct nl80211_noise_info*) ; 
 int /*<<< orphan*/  nl80211_update_scan_res_noise (int /*<<< orphan*/ ,struct nl80211_noise_info*) ; 
 struct wpa_scan_results* os_zalloc (int) ; 
 int send_and_recv_msgs (struct wpa_driver_nl80211_data*,struct nl_msg*,int /*<<< orphan*/ ,struct nl80211_bss_info_arg*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  wpa_scan_results_free (struct wpa_scan_results*) ; 

__attribute__((used)) static struct wpa_scan_results *
nl80211_get_scan_results(struct wpa_driver_nl80211_data *drv)
{
	struct nl_msg *msg;
	struct wpa_scan_results *res;
	int ret;
	struct nl80211_bss_info_arg arg;

	res = os_zalloc(sizeof(*res));
	if (res == NULL)
		return NULL;
	if (!(msg = nl80211_cmd_msg(drv->first_bss, NLM_F_DUMP,
				    NL80211_CMD_GET_SCAN))) {
		wpa_scan_results_free(res);
		return NULL;
	}

	arg.drv = drv;
	arg.res = res;
	ret = send_and_recv_msgs(drv, msg, bss_info_handler, &arg);
	if (ret == 0) {
		struct nl80211_noise_info info;

		wpa_printf(MSG_DEBUG, "nl80211: Received scan results (%lu "
			   "BSSes)", (unsigned long) res->num);
		if (nl80211_get_noise_for_scan_results(drv, &info) == 0) {
			size_t i;

			for (i = 0; i < res->num; ++i)
				nl80211_update_scan_res_noise(res->res[i],
							      &info);
		}
		return res;
	}
	wpa_printf(MSG_DEBUG, "nl80211: Scan result fetch failed: ret=%d "
		   "(%s)", ret, strerror(-ret));
	wpa_scan_results_free(res);
	return NULL;
}