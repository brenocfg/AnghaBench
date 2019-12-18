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
struct wpa_supplicant {int p2p_in_provisioning; int p2p_in_invitation; scalar_t__ p2p_invite_go_freq; scalar_t__ wps_freq; scalar_t__ known_wps_freq; scalar_t__ after_wps; TYPE_1__* go_params; } ;
struct wpa_driver_scan_params {scalar_t__* freqs; } ;
struct TYPE_2__ {scalar_t__ freq; scalar_t__* freq_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  int_array_concat (scalar_t__**,scalar_t__*) ; 
 int /*<<< orphan*/  int_array_sort_unique (scalar_t__*) ; 
 void* os_calloc (int,int) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void wpa_supplicant_optimize_freqs(
	struct wpa_supplicant *wpa_s, struct wpa_driver_scan_params *params)
{
#ifdef CONFIG_P2P
	if (params->freqs == NULL && wpa_s->p2p_in_provisioning &&
	    wpa_s->go_params) {
		/* Optimize provisioning state scan based on GO information */
		if (wpa_s->p2p_in_provisioning < 5 &&
		    wpa_s->go_params->freq > 0) {
			wpa_dbg(wpa_s, MSG_DEBUG, "P2P: Scan only GO "
				"preferred frequency %d MHz",
				wpa_s->go_params->freq);
			params->freqs = os_calloc(2, sizeof(int));
			if (params->freqs)
				params->freqs[0] = wpa_s->go_params->freq;
		} else if (wpa_s->p2p_in_provisioning < 8 &&
			   wpa_s->go_params->freq_list[0]) {
			wpa_dbg(wpa_s, MSG_DEBUG, "P2P: Scan only common "
				"channels");
			int_array_concat(&params->freqs,
					 wpa_s->go_params->freq_list);
			if (params->freqs)
				int_array_sort_unique(params->freqs);
		}
		wpa_s->p2p_in_provisioning++;
	}

	if (params->freqs == NULL && wpa_s->p2p_in_invitation) {
		/*
		 * Optimize scan based on GO information during persistent
		 * group reinvocation
		 */
		if (wpa_s->p2p_in_invitation < 5 &&
		    wpa_s->p2p_invite_go_freq > 0) {
			wpa_dbg(wpa_s, MSG_DEBUG, "P2P: Scan only GO preferred frequency %d MHz during invitation",
				wpa_s->p2p_invite_go_freq);
			params->freqs = os_calloc(2, sizeof(int));
			if (params->freqs)
				params->freqs[0] = wpa_s->p2p_invite_go_freq;
		}
		wpa_s->p2p_in_invitation++;
		if (wpa_s->p2p_in_invitation > 20) {
			/*
			 * This should not really happen since the variable is
			 * cleared on group removal, but if it does happen, make
			 * sure we do not get stuck in special invitation scan
			 * mode.
			 */
			wpa_dbg(wpa_s, MSG_DEBUG, "P2P: Clear p2p_in_invitation");
			wpa_s->p2p_in_invitation = 0;
		}
	}
#endif /* CONFIG_P2P */

#ifdef CONFIG_WPS
	if (params->freqs == NULL && wpa_s->after_wps && wpa_s->wps_freq) {
		/*
		 * Optimize post-provisioning scan based on channel used
		 * during provisioning.
		 */
		wpa_dbg(wpa_s, MSG_DEBUG, "WPS: Scan only frequency %u MHz "
			"that was used during provisioning", wpa_s->wps_freq);
		params->freqs = os_calloc(2, sizeof(int));
		if (params->freqs)
			params->freqs[0] = wpa_s->wps_freq;
		wpa_s->after_wps--;
	} else if (wpa_s->after_wps)
		wpa_s->after_wps--;

	if (params->freqs == NULL && wpa_s->known_wps_freq && wpa_s->wps_freq)
	{
		/* Optimize provisioning scan based on already known channel */
		wpa_dbg(wpa_s, MSG_DEBUG, "WPS: Scan only frequency %u MHz",
			wpa_s->wps_freq);
		params->freqs = os_calloc(2, sizeof(int));
		if (params->freqs)
			params->freqs[0] = wpa_s->wps_freq;
		wpa_s->known_wps_freq = 0; /* only do this once */
	}
#endif /* CONFIG_WPS */
}