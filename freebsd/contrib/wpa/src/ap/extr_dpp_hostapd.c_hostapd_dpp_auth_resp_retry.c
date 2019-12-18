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
struct hostapd_data {int dpp_resp_max_tries; int dpp_resp_retry_time; struct dpp_authentication* dpp_auth; } ;
struct dpp_authentication {unsigned int auth_resp_tries; int /*<<< orphan*/  resp_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  dpp_auth_deinit (struct dpp_authentication*) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (unsigned int,unsigned int,int /*<<< orphan*/ ,struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_dpp_auth_resp_retry_timeout ; 
 int /*<<< orphan*/  hostapd_drv_send_action_cancel_wait (struct hostapd_data*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void hostapd_dpp_auth_resp_retry(struct hostapd_data *hapd)
{
	struct dpp_authentication *auth = hapd->dpp_auth;
	unsigned int wait_time, max_tries;

	if (!auth || !auth->resp_msg)
		return;

	if (hapd->dpp_resp_max_tries)
		max_tries = hapd->dpp_resp_max_tries;
	else
		max_tries = 5;
	auth->auth_resp_tries++;
	if (auth->auth_resp_tries >= max_tries) {
		wpa_printf(MSG_INFO,
			   "DPP: No confirm received from initiator - stopping exchange");
		hostapd_drv_send_action_cancel_wait(hapd);
		dpp_auth_deinit(hapd->dpp_auth);
		hapd->dpp_auth = NULL;
		return;
	}

	if (hapd->dpp_resp_retry_time)
		wait_time = hapd->dpp_resp_retry_time;
	else
		wait_time = 1000;
	wpa_printf(MSG_DEBUG,
		   "DPP: Schedule retransmission of Authentication Response frame in %u ms",
		wait_time);
	eloop_cancel_timeout(hostapd_dpp_auth_resp_retry_timeout, hapd, NULL);
	eloop_register_timeout(wait_time / 1000,
			       (wait_time % 1000) * 1000,
			       hostapd_dpp_auth_resp_retry_timeout, hapd, NULL);
}