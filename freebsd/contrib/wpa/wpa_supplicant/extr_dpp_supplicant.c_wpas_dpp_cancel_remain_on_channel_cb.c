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
struct wpa_supplicant {int dpp_listen_freq; TYPE_1__* dpp_auth; scalar_t__ dpp_in_response_listen; } ;
struct TYPE_2__ {unsigned int neg_freq; unsigned int curr_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  wpas_dpp_listen_start (struct wpa_supplicant*,unsigned int) ; 
 int /*<<< orphan*/  wpas_dpp_listen_work_done (struct wpa_supplicant*) ; 

void wpas_dpp_cancel_remain_on_channel_cb(struct wpa_supplicant *wpa_s,
					  unsigned int freq)
{
	wpas_dpp_listen_work_done(wpa_s);

	if (wpa_s->dpp_auth && wpa_s->dpp_in_response_listen) {
		unsigned int new_freq;

		/* Continue listen with a new remain-on-channel */
		if (wpa_s->dpp_auth->neg_freq > 0)
			new_freq = wpa_s->dpp_auth->neg_freq;
		else
			new_freq = wpa_s->dpp_auth->curr_freq;
		wpa_printf(MSG_DEBUG,
			   "DPP: Continue wait on %u MHz for the ongoing DPP provisioning session",
			   new_freq);
		wpas_dpp_listen_start(wpa_s, new_freq);
		return;
	}

	if (wpa_s->dpp_listen_freq) {
		/* Continue listen with a new remain-on-channel */
		wpas_dpp_listen_start(wpa_s, wpa_s->dpp_listen_freq);
	}
}