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
struct wpa_driver_scan_params {int num_ssids; int* freqs; TYPE_1__* ssids; } ;
struct bgscan_learn_data {int /*<<< orphan*/  last_bgscan; int /*<<< orphan*/  scan_interval; TYPE_2__* ssid; struct wpa_supplicant* wpa_s; } ;
typedef  int /*<<< orphan*/  params ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_4__ {int* scan_freq; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_3__ {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int* bgscan_learn_get_freqs (struct bgscan_learn_data*,size_t*) ; 
 int* bgscan_learn_get_probe_freq (struct bgscan_learn_data*,int*,size_t) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (void*,void*),struct bgscan_learn_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (int*) ; 
 int /*<<< orphan*/  os_get_reltime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memset (struct wpa_driver_scan_params*,int /*<<< orphan*/ ,int) ; 
 int os_snprintf (char*,int,char*,int) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wpa_supplicant_trigger_scan (struct wpa_supplicant*,struct wpa_driver_scan_params*) ; 

__attribute__((used)) static void bgscan_learn_timeout(void *eloop_ctx, void *timeout_ctx)
{
	struct bgscan_learn_data *data = eloop_ctx;
	struct wpa_supplicant *wpa_s = data->wpa_s;
	struct wpa_driver_scan_params params;
	int *freqs = NULL;
	size_t count, i;
	char msg[100], *pos;

	os_memset(&params, 0, sizeof(params));
	params.num_ssids = 1;
	params.ssids[0].ssid = data->ssid->ssid;
	params.ssids[0].ssid_len = data->ssid->ssid_len;
	if (data->ssid->scan_freq)
		params.freqs = data->ssid->scan_freq;
	else {
		freqs = bgscan_learn_get_freqs(data, &count);
		wpa_printf(MSG_DEBUG, "bgscan learn: BSSes in this ESS have "
			   "been seen on %u channels", (unsigned int) count);
		freqs = bgscan_learn_get_probe_freq(data, freqs, count);

		msg[0] = '\0';
		pos = msg;
		for (i = 0; freqs && freqs[i]; i++) {
			int ret;
			ret = os_snprintf(pos, msg + sizeof(msg) - pos, " %d",
					  freqs[i]);
			if (os_snprintf_error(msg + sizeof(msg) - pos, ret))
				break;
			pos += ret;
		}
		pos[0] = '\0';
		wpa_printf(MSG_DEBUG, "bgscan learn: Scanning frequencies:%s",
			   msg);
		params.freqs = freqs;
	}

	wpa_printf(MSG_DEBUG, "bgscan learn: Request a background scan");
	if (wpa_supplicant_trigger_scan(wpa_s, &params)) {
		wpa_printf(MSG_DEBUG, "bgscan learn: Failed to trigger scan");
		eloop_register_timeout(data->scan_interval, 0,
				       bgscan_learn_timeout, data, NULL);
	} else
		os_get_reltime(&data->last_bgscan);
	os_free(freqs);
}