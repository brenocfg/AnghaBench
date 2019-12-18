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
struct wpa_supplicant {int dummy; } ;
struct wpa_driver_scan_params {int num_ssids; int /*<<< orphan*/  freqs; TYPE_1__* ssids; } ;
struct bgscan_simple_data {scalar_t__ scan_interval; scalar_t__ short_interval; scalar_t__ short_scan_count; scalar_t__ max_short_scans; scalar_t__ long_interval; int /*<<< orphan*/  last_bgscan; TYPE_2__* ssid; struct wpa_supplicant* wpa_s; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_4__ {int /*<<< orphan*/  scan_freq; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_3__ {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_register_timeout (scalar_t__,int /*<<< orphan*/ ,void (*) (void*,void*),struct bgscan_simple_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_get_reltime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memset (struct wpa_driver_scan_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpa_supplicant_trigger_scan (struct wpa_supplicant*,struct wpa_driver_scan_params*) ; 

__attribute__((used)) static void bgscan_simple_timeout(void *eloop_ctx, void *timeout_ctx)
{
	struct bgscan_simple_data *data = eloop_ctx;
	struct wpa_supplicant *wpa_s = data->wpa_s;
	struct wpa_driver_scan_params params;

	os_memset(&params, 0, sizeof(params));
	params.num_ssids = 1;
	params.ssids[0].ssid = data->ssid->ssid;
	params.ssids[0].ssid_len = data->ssid->ssid_len;
	params.freqs = data->ssid->scan_freq;

	/*
	 * A more advanced bgscan module would learn about most like channels
	 * over time and request scans only for some channels (probing others
	 * every now and then) to reduce effect on the data connection.
	 */

	wpa_printf(MSG_DEBUG, "bgscan simple: Request a background scan");
	if (wpa_supplicant_trigger_scan(wpa_s, &params)) {
		wpa_printf(MSG_DEBUG, "bgscan simple: Failed to trigger scan");
		eloop_register_timeout(data->scan_interval, 0,
				       bgscan_simple_timeout, data, NULL);
	} else {
		if (data->scan_interval == data->short_interval) {
			data->short_scan_count++;
			if (data->short_scan_count >= data->max_short_scans) {
				data->scan_interval = data->long_interval;
				wpa_printf(MSG_DEBUG, "bgscan simple: Backing "
					   "off to long scan interval");
			}
		} else if (data->short_scan_count > 0) {
			/*
			 * If we lasted a long scan interval without any
			 * CQM triggers, decrease the short-scan count,
			 * which allows 1 more short-scan interval to
			 * occur in the future when CQM triggers.
			 */
			data->short_scan_count--;
		}
		os_get_reltime(&data->last_bgscan);
	}
}