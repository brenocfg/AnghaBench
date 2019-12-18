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
struct wpa_scan_results {int dummy; } ;
struct autoscan_exponential_data {int interval; int limit; int base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int autoscan_exponential_notify_scan(void *priv,
					    struct wpa_scan_results *scan_res)
{
	struct autoscan_exponential_data *data = priv;

	wpa_printf(MSG_DEBUG, "autoscan exponential: scan result "
		   "notification");

	if (data->interval >= data->limit)
		return data->limit;

	if (data->interval <= 0)
		data->interval = data->base;
	else {
		data->interval = data->interval * data->base;
		if (data->interval > data->limit)
			return data->limit;
	}

	return data->interval;
}