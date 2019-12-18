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
struct wpa_supplicant {int dpp_resp_wait_time; int dpp_in_response_listen; struct dpp_authentication* dpp_auth; int /*<<< orphan*/  dpp_last_init; } ;
struct os_reltime {int sec; int usec; } ;
struct dpp_authentication {unsigned int curr_freq; unsigned int neg_freq; scalar_t__ auth_req_ack; int /*<<< orphan*/  waiting_auth_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPP_EVENT_AUTH_INIT_FAILED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  dpp_auth_deinit (struct dpp_authentication*) ; 
 int /*<<< orphan*/  eloop_register_timeout (unsigned int,unsigned int,void (*) (void*,void*),struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  offchannel_send_action_done (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  os_get_reltime (struct os_reltime*) ; 
 int /*<<< orphan*/  os_reltime_sub (struct os_reltime*,int /*<<< orphan*/ *,struct os_reltime*) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpas_dpp_auth_init_next (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_dpp_listen_start (struct wpa_supplicant*,unsigned int) ; 
 int /*<<< orphan*/  wpas_dpp_listen_stop (struct wpa_supplicant*) ; 

__attribute__((used)) static void wpas_dpp_reply_wait_timeout(void *eloop_ctx, void *timeout_ctx)
{
	struct wpa_supplicant *wpa_s = eloop_ctx;
	struct dpp_authentication *auth = wpa_s->dpp_auth;
	unsigned int freq;
	struct os_reltime now, diff;
	unsigned int wait_time, diff_ms;

	if (!auth || !auth->waiting_auth_resp)
		return;

	wait_time = wpa_s->dpp_resp_wait_time ?
		wpa_s->dpp_resp_wait_time : 2000;
	os_get_reltime(&now);
	os_reltime_sub(&now, &wpa_s->dpp_last_init, &diff);
	diff_ms = diff.sec * 1000 + diff.usec / 1000;
	wpa_printf(MSG_DEBUG,
		   "DPP: Reply wait timeout - wait_time=%u diff_ms=%u",
		   wait_time, diff_ms);

	if (auth->auth_req_ack && diff_ms >= wait_time) {
		/* Peer ACK'ed Authentication Request frame, but did not reply
		 * with Authentication Response frame within two seconds. */
		wpa_printf(MSG_INFO,
			   "DPP: No response received from responder - stopping initiation attempt");
		wpa_msg(wpa_s, MSG_INFO, DPP_EVENT_AUTH_INIT_FAILED);
		offchannel_send_action_done(wpa_s);
		wpas_dpp_listen_stop(wpa_s);
		dpp_auth_deinit(auth);
		wpa_s->dpp_auth = NULL;
		return;
	}

	if (diff_ms >= wait_time) {
		/* Authentication Request frame was not ACK'ed and no reply
		 * was receiving within two seconds. */
		wpa_printf(MSG_DEBUG,
			   "DPP: Continue Initiator channel iteration");
		offchannel_send_action_done(wpa_s);
		wpas_dpp_listen_stop(wpa_s);
		wpas_dpp_auth_init_next(wpa_s);
		return;
	}

	/* Driver did not support 2000 ms long wait_time with TX command, so
	 * schedule listen operation to continue waiting for the response.
	 *
	 * DPP listen operations continue until stopped, so simply schedule a
	 * new call to this function at the point when the two second reply
	 * wait has expired. */
	wait_time -= diff_ms;

	freq = auth->curr_freq;
	if (auth->neg_freq > 0)
		freq = auth->neg_freq;
	wpa_printf(MSG_DEBUG,
		   "DPP: Continue reply wait on channel %u MHz for %u ms",
		   freq, wait_time);
	wpa_s->dpp_in_response_listen = 1;
	wpas_dpp_listen_start(wpa_s, freq);

	eloop_register_timeout(wait_time / 1000, (wait_time % 1000) * 1000,
			       wpas_dpp_reply_wait_timeout, wpa_s, NULL);
}