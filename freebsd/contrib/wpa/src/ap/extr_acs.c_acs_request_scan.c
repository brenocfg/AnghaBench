#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wpa_driver_scan_params {int* freqs; } ;
struct hostapd_iface {int /*<<< orphan*/ * bss; TYPE_2__* conf; scalar_t__ acs_num_completed_scans; int /*<<< orphan*/  scan_cb; TYPE_1__* current_mode; } ;
struct hostapd_channel_data {int flag; int /*<<< orphan*/  freq; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_4__ {int /*<<< orphan*/  acs_num_scans; } ;
struct TYPE_3__ {int num_channels; struct hostapd_channel_data* channels; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_DISABLED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  acs_cleanup (struct hostapd_iface*) ; 
 int /*<<< orphan*/  acs_scan_complete ; 
 scalar_t__ hostapd_driver_scan (int /*<<< orphan*/ ,struct wpa_driver_scan_params*) ; 
 int /*<<< orphan*/  is_in_chanlist (struct hostapd_iface*,struct hostapd_channel_data*) ; 
 int* os_calloc (int,int) ; 
 int /*<<< orphan*/  os_free (int*) ; 
 int /*<<< orphan*/  os_memset (struct wpa_driver_scan_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int acs_request_scan(struct hostapd_iface *iface)
{
	struct wpa_driver_scan_params params;
	struct hostapd_channel_data *chan;
	int i, *freq;

	os_memset(&params, 0, sizeof(params));
	params.freqs = os_calloc(iface->current_mode->num_channels + 1,
				 sizeof(params.freqs[0]));
	if (params.freqs == NULL)
		return -1;

	freq = params.freqs;
	for (i = 0; i < iface->current_mode->num_channels; i++) {
		chan = &iface->current_mode->channels[i];
		if (chan->flag & HOSTAPD_CHAN_DISABLED)
			continue;

		if (!is_in_chanlist(iface, chan))
			continue;

		*freq++ = chan->freq;
	}
	*freq = 0;

	iface->scan_cb = acs_scan_complete;

	wpa_printf(MSG_DEBUG, "ACS: Scanning %d / %d",
		   iface->acs_num_completed_scans + 1,
		   iface->conf->acs_num_scans);

	if (hostapd_driver_scan(iface->bss[0], &params) < 0) {
		wpa_printf(MSG_ERROR, "ACS: Failed to request initial scan");
		acs_cleanup(iface);
		os_free(params.freqs);
		return -1;
	}

	os_free(params.freqs);
	return 0;
}