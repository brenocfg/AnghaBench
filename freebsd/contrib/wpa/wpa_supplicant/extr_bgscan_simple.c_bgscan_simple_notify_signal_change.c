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
struct os_reltime {scalar_t__ sec; } ;
struct TYPE_2__ {scalar_t__ sec; } ;
struct bgscan_simple_data {scalar_t__ short_interval; scalar_t__ long_interval; scalar_t__ signal_threshold; scalar_t__ scan_interval; scalar_t__ short_scan_count; scalar_t__ max_short_scans; TYPE_1__ last_bgscan; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  bgscan_simple_timeout ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct bgscan_simple_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bgscan_simple_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_get_reltime (struct os_reltime*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void bgscan_simple_notify_signal_change(void *priv, int above,
					       int current_signal,
					       int current_noise,
					       int current_txrate)
{
	struct bgscan_simple_data *data = priv;
	int scan = 0;
	struct os_reltime now;

	if (data->short_interval == data->long_interval ||
	    data->signal_threshold == 0)
		return;

	wpa_printf(MSG_DEBUG, "bgscan simple: signal level changed "
		   "(above=%d current_signal=%d current_noise=%d "
		   "current_txrate=%d))", above, current_signal,
		   current_noise, current_txrate);
	if (data->scan_interval == data->long_interval && !above) {
		wpa_printf(MSG_DEBUG, "bgscan simple: Start using short "
			   "bgscan interval");
		data->scan_interval = data->short_interval;
		os_get_reltime(&now);
		if (now.sec > data->last_bgscan.sec + 1 &&
		    data->short_scan_count <= data->max_short_scans)
			/*
			 * If we haven't just previously (<1 second ago)
			 * performed a scan, and we haven't depleted our
			 * budget for short-scans, perform a scan
			 * immediately.
			 */
			scan = 1;
		else if (data->last_bgscan.sec + data->long_interval >
			 now.sec + data->scan_interval) {
			/*
			 * Restart scan interval timer if currently scheduled
			 * scan is too far in the future.
			 */
			eloop_cancel_timeout(bgscan_simple_timeout, data,
					     NULL);
			eloop_register_timeout(data->scan_interval, 0,
					       bgscan_simple_timeout, data,
					       NULL);
		}
	} else if (data->scan_interval == data->short_interval && above) {
		wpa_printf(MSG_DEBUG, "bgscan simple: Start using long bgscan "
			   "interval");
		data->scan_interval = data->long_interval;
		eloop_cancel_timeout(bgscan_simple_timeout, data, NULL);
		eloop_register_timeout(data->scan_interval, 0,
				       bgscan_simple_timeout, data, NULL);
	} else if (!above) {
		/*
		 * Signal dropped further 4 dB. Request a new scan if we have
		 * not yet scanned in a while.
		 */
		os_get_reltime(&now);
		if (now.sec > data->last_bgscan.sec + 10)
			scan = 1;
	}

	if (scan) {
		wpa_printf(MSG_DEBUG, "bgscan simple: Trigger immediate scan");
		eloop_cancel_timeout(bgscan_simple_timeout, data, NULL);
		eloop_register_timeout(0, 0, bgscan_simple_timeout, data,
				       NULL);
	}
}