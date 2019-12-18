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
typedef  int /*<<< orphan*/  u32 ;
struct wpa_driver_nl80211_data {int dummy; } ;
struct nl_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_CMD_GET_PROTOCOL_FEATURES ; 
 int /*<<< orphan*/  nl80211_cmd (struct wpa_driver_nl80211_data*,struct nl_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nl_msg* nlmsg_alloc () ; 
 int /*<<< orphan*/  nlmsg_free (struct nl_msg*) ; 
 int /*<<< orphan*/  protocol_feature_handler ; 
 scalar_t__ send_and_recv_msgs (struct wpa_driver_nl80211_data*,struct nl_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 get_nl80211_protocol_features(struct wpa_driver_nl80211_data *drv)
{
	u32 feat = 0;
	struct nl_msg *msg;

	msg = nlmsg_alloc();
	if (!msg)
		return 0;

	if (!nl80211_cmd(drv, msg, 0, NL80211_CMD_GET_PROTOCOL_FEATURES)) {
		nlmsg_free(msg);
		return 0;
	}

	if (send_and_recv_msgs(drv, msg, protocol_feature_handler, &feat) == 0)
		return feat;

	return 0;
}