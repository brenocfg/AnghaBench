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
struct wpa_supplicant {unsigned int scan_id_count; int /*<<< orphan*/ * scan_id; int /*<<< orphan*/  conf; } ;
struct wpa_ssid {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; scalar_t__ scan_ssid; } ;
struct wpa_driver_scan_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_add_owe_scan_ssid (struct wpa_supplicant*,struct wpa_driver_scan_params*,struct wpa_ssid*,size_t) ; 
 int /*<<< orphan*/  wpa_add_scan_ssid (struct wpa_supplicant*,struct wpa_driver_scan_params*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wpa_ssid* wpa_config_get_network (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpa_set_scan_ssids(struct wpa_supplicant *wpa_s,
			       struct wpa_driver_scan_params *params,
			       size_t max_ssids)
{
	unsigned int i;
	struct wpa_ssid *ssid;

	/*
	 * For devices with max_ssids greater than 1, leave the last slot empty
	 * for adding the wildcard scan entry.
	 */
	max_ssids = max_ssids > 1 ? max_ssids - 1 : max_ssids;

	for (i = 0; i < wpa_s->scan_id_count; i++) {
		ssid = wpa_config_get_network(wpa_s->conf, wpa_s->scan_id[i]);
		if (!ssid)
			continue;
		if (ssid->scan_ssid)
			wpa_add_scan_ssid(wpa_s, params, max_ssids,
					  ssid->ssid, ssid->ssid_len);
		/*
		 * Also add the SSID of the OWE BSS, to allow discovery of
		 * transition mode APs more quickly.
		 */
		wpa_add_owe_scan_ssid(wpa_s, params, ssid, max_ssids);
	}

	wpa_s->scan_id_count = 0;
}