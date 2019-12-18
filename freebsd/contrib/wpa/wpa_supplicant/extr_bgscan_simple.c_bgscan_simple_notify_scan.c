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
struct bgscan_simple_data {int /*<<< orphan*/  scan_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  bgscan_simple_timeout ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct bgscan_simple_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bgscan_simple_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int bgscan_simple_notify_scan(void *priv,
				     struct wpa_scan_results *scan_res)
{
	struct bgscan_simple_data *data = priv;

	wpa_printf(MSG_DEBUG, "bgscan simple: scan result notification");

	eloop_cancel_timeout(bgscan_simple_timeout, data, NULL);
	eloop_register_timeout(data->scan_interval, 0, bgscan_simple_timeout,
			       data, NULL);

	/*
	 * A more advanced bgscan could process scan results internally, select
	 * the BSS and request roam if needed. This sample uses the existing
	 * BSS/ESS selection routine. Change this to return 1 if selection is
	 * done inside the bgscan module.
	 */

	return 0;
}