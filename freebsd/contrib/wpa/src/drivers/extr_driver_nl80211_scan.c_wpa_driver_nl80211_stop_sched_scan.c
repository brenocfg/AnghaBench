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
struct TYPE_2__ {int /*<<< orphan*/  sched_scan_supported; } ;
struct wpa_driver_nl80211_data {TYPE_1__ capa; } ;
struct nl_msg {int dummy; } ;
struct i802_bss {struct wpa_driver_nl80211_data* drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  NL80211_CMD_STOP_SCHED_SCAN ; 
 int android_pno_stop (struct i802_bss*) ; 
 struct nl_msg* nl80211_drv_msg (struct wpa_driver_nl80211_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int send_and_recv_msgs (struct wpa_driver_nl80211_data*,struct nl_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int wpa_driver_nl80211_stop_sched_scan(void *priv)
{
	struct i802_bss *bss = priv;
	struct wpa_driver_nl80211_data *drv = bss->drv;
	int ret;
	struct nl_msg *msg;

#ifdef ANDROID
	if (!drv->capa.sched_scan_supported)
		return android_pno_stop(bss);
#endif /* ANDROID */

	msg = nl80211_drv_msg(drv, 0, NL80211_CMD_STOP_SCHED_SCAN);
	ret = send_and_recv_msgs(drv, msg, NULL, NULL);
	if (ret) {
		wpa_printf(MSG_DEBUG,
			   "nl80211: Sched scan stop failed: ret=%d (%s)",
			   ret, strerror(-ret));
	} else {
		wpa_printf(MSG_DEBUG,
			   "nl80211: Sched scan stop sent");
	}

	return ret;
}