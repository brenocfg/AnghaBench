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
struct wpabuf {int dummy; } ;
struct wpa_supplicant {struct dpp_authentication* dpp_auth; } ;
struct dpp_authentication {int peer_version; scalar_t__ conf_resp_status; int waiting_conf_result; struct wpabuf* conf_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPP_EVENT_CONF_FAILED ; 
 int /*<<< orphan*/  DPP_EVENT_CONF_SENT ; 
 scalar_t__ DPP_STATUS_OK ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  dpp_auth_deinit (struct dpp_authentication*) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  offchannel_send_action_done (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpas_dpp_auth_resp_retry_timeout ; 
 int /*<<< orphan*/  wpas_dpp_config_result_wait_timeout ; 
 int /*<<< orphan*/  wpas_dpp_listen_stop (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_dpp_reply_wait_timeout ; 

__attribute__((used)) static void
wpas_dpp_gas_status_handler(void *ctx, struct wpabuf *resp, int ok)
{
	struct wpa_supplicant *wpa_s = ctx;
	struct dpp_authentication *auth = wpa_s->dpp_auth;

	if (!auth) {
		wpabuf_free(resp);
		return;
	}
	if (auth->conf_resp != resp) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Ignore GAS status report (ok=%d) for unknown response",
			ok);
		wpabuf_free(resp);
		return;
	}

	wpa_printf(MSG_DEBUG, "DPP: Configuration exchange completed (ok=%d)",
		   ok);
	eloop_cancel_timeout(wpas_dpp_reply_wait_timeout, wpa_s, NULL);
	eloop_cancel_timeout(wpas_dpp_auth_resp_retry_timeout, wpa_s, NULL);
#ifdef CONFIG_DPP2
	if (ok && auth->peer_version >= 2 &&
	    auth->conf_resp_status == DPP_STATUS_OK) {
		wpa_printf(MSG_DEBUG, "DPP: Wait for Configuration Result");
		auth->waiting_conf_result = 1;
		auth->conf_resp = NULL;
		wpabuf_free(resp);
		eloop_cancel_timeout(wpas_dpp_config_result_wait_timeout,
				     wpa_s, NULL);
		eloop_register_timeout(2, 0,
				       wpas_dpp_config_result_wait_timeout,
				       wpa_s, NULL);
		return;
	}
#endif /* CONFIG_DPP2 */
	offchannel_send_action_done(wpa_s);
	wpas_dpp_listen_stop(wpa_s);
	if (ok)
		wpa_msg(wpa_s, MSG_INFO, DPP_EVENT_CONF_SENT);
	else
		wpa_msg(wpa_s, MSG_INFO, DPP_EVENT_CONF_FAILED);
	dpp_auth_deinit(wpa_s->dpp_auth);
	wpa_s->dpp_auth = NULL;
	wpabuf_free(resp);
}