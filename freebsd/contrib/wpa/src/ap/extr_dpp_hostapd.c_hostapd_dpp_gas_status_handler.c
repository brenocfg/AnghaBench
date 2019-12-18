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
struct hostapd_data {struct dpp_authentication* dpp_auth; int /*<<< orphan*/  msg_ctx; } ;
struct dpp_authentication {int peer_version; scalar_t__ conf_resp_status; int waiting_conf_result; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPP_EVENT_CONF_FAILED ; 
 int /*<<< orphan*/  DPP_EVENT_CONF_SENT ; 
 scalar_t__ DPP_STATUS_OK ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  dpp_auth_deinit (struct dpp_authentication*) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_dpp_auth_resp_retry_timeout ; 
 int /*<<< orphan*/  hostapd_dpp_config_result_wait_timeout ; 
 int /*<<< orphan*/  hostapd_dpp_reply_wait_timeout ; 
 int /*<<< orphan*/  hostapd_drv_send_action_cancel_wait (struct hostapd_data*) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

void hostapd_dpp_gas_status_handler(struct hostapd_data *hapd, int ok)
{
	struct dpp_authentication *auth = hapd->dpp_auth;

	if (!auth)
		return;

	wpa_printf(MSG_DEBUG, "DPP: Configuration exchange completed (ok=%d)",
		   ok);
	eloop_cancel_timeout(hostapd_dpp_reply_wait_timeout, hapd, NULL);
	eloop_cancel_timeout(hostapd_dpp_auth_resp_retry_timeout, hapd, NULL);
#ifdef CONFIG_DPP2
	if (ok && auth->peer_version >= 2 &&
	    auth->conf_resp_status == DPP_STATUS_OK) {
		wpa_printf(MSG_DEBUG, "DPP: Wait for Configuration Result");
		auth->waiting_conf_result = 1;
		eloop_cancel_timeout(hostapd_dpp_config_result_wait_timeout,
				     hapd, NULL);
		eloop_register_timeout(2, 0,
				       hostapd_dpp_config_result_wait_timeout,
				       hapd, NULL);
		return;
	}
#endif /* CONFIG_DPP2 */
	hostapd_drv_send_action_cancel_wait(hapd);

	if (ok)
		wpa_msg(hapd->msg_ctx, MSG_INFO, DPP_EVENT_CONF_SENT);
	else
		wpa_msg(hapd->msg_ctx, MSG_INFO, DPP_EVENT_CONF_FAILED);
	dpp_auth_deinit(hapd->dpp_auth);
	hapd->dpp_auth = NULL;
}