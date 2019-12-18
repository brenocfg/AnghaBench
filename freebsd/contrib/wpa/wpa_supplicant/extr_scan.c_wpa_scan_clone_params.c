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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_driver_scan_params {size_t num_ssids; int extra_ies_len; int num_filter_ssids; int sched_scan_plans_num; int /*<<< orphan*/  relative_adjust_rssi; int /*<<< orphan*/  relative_adjust_band; int /*<<< orphan*/  relative_rssi; int /*<<< orphan*/  relative_rssi_set; int /*<<< orphan*/ * bssid; int /*<<< orphan*/ * mac_addr_mask; int /*<<< orphan*/ * mac_addr; scalar_t__ mac_addr_rand; int /*<<< orphan*/ * sched_scan_plans; int /*<<< orphan*/  oce_scan; int /*<<< orphan*/  duration_mandatory; int /*<<< orphan*/  duration; int /*<<< orphan*/  low_priority; int /*<<< orphan*/  only_new_results; int /*<<< orphan*/  p2p_probe; int /*<<< orphan*/  filter_rssi; int /*<<< orphan*/ * filter_ssids; int /*<<< orphan*/ * freqs; int /*<<< orphan*/ * extra_ies; TYPE_1__* ssids; } ;
struct TYPE_2__ {int ssid_len; int /*<<< orphan*/ * ssid; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int int_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* os_memdup (int /*<<< orphan*/ *,int) ; 
 struct wpa_driver_scan_params* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_scan_free_params (struct wpa_driver_scan_params*) ; 

struct wpa_driver_scan_params *
wpa_scan_clone_params(const struct wpa_driver_scan_params *src)
{
	struct wpa_driver_scan_params *params;
	size_t i;
	u8 *n;

	params = os_zalloc(sizeof(*params));
	if (params == NULL)
		return NULL;

	for (i = 0; i < src->num_ssids; i++) {
		if (src->ssids[i].ssid) {
			n = os_memdup(src->ssids[i].ssid,
				      src->ssids[i].ssid_len);
			if (n == NULL)
				goto failed;
			params->ssids[i].ssid = n;
			params->ssids[i].ssid_len = src->ssids[i].ssid_len;
		}
	}
	params->num_ssids = src->num_ssids;

	if (src->extra_ies) {
		n = os_memdup(src->extra_ies, src->extra_ies_len);
		if (n == NULL)
			goto failed;
		params->extra_ies = n;
		params->extra_ies_len = src->extra_ies_len;
	}

	if (src->freqs) {
		int len = int_array_len(src->freqs);
		params->freqs = os_memdup(src->freqs, (len + 1) * sizeof(int));
		if (params->freqs == NULL)
			goto failed;
	}

	if (src->filter_ssids) {
		params->filter_ssids = os_memdup(src->filter_ssids,
						 sizeof(*params->filter_ssids) *
						 src->num_filter_ssids);
		if (params->filter_ssids == NULL)
			goto failed;
		params->num_filter_ssids = src->num_filter_ssids;
	}

	params->filter_rssi = src->filter_rssi;
	params->p2p_probe = src->p2p_probe;
	params->only_new_results = src->only_new_results;
	params->low_priority = src->low_priority;
	params->duration = src->duration;
	params->duration_mandatory = src->duration_mandatory;
	params->oce_scan = src->oce_scan;

	if (src->sched_scan_plans_num > 0) {
		params->sched_scan_plans =
			os_memdup(src->sched_scan_plans,
				  sizeof(*src->sched_scan_plans) *
				  src->sched_scan_plans_num);
		if (!params->sched_scan_plans)
			goto failed;

		params->sched_scan_plans_num = src->sched_scan_plans_num;
	}

	if (src->mac_addr_rand) {
		params->mac_addr_rand = src->mac_addr_rand;

		if (src->mac_addr && src->mac_addr_mask) {
			u8 *mac_addr;

			mac_addr = os_malloc(2 * ETH_ALEN);
			if (!mac_addr)
				goto failed;

			os_memcpy(mac_addr, src->mac_addr, ETH_ALEN);
			os_memcpy(mac_addr + ETH_ALEN, src->mac_addr_mask,
				  ETH_ALEN);
			params->mac_addr = mac_addr;
			params->mac_addr_mask = mac_addr + ETH_ALEN;
		}
	}

	if (src->bssid) {
		u8 *bssid;

		bssid = os_memdup(src->bssid, ETH_ALEN);
		if (!bssid)
			goto failed;
		params->bssid = bssid;
	}

	params->relative_rssi_set = src->relative_rssi_set;
	params->relative_rssi = src->relative_rssi;
	params->relative_adjust_band = src->relative_adjust_band;
	params->relative_adjust_rssi = src->relative_adjust_rssi;
	return params;

failed:
	wpa_scan_free_params(params);
	return NULL;
}