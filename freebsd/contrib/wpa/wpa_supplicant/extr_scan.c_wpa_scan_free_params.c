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
struct wpa_driver_scan_params {size_t num_ssids; scalar_t__ bssid; scalar_t__ mac_addr; struct wpa_driver_scan_params* sched_scan_plans; struct wpa_driver_scan_params* filter_ssids; struct wpa_driver_scan_params* freqs; scalar_t__ extra_ies; TYPE_1__* ssids; } ;
typedef  struct wpa_driver_scan_params u8 ;
struct TYPE_2__ {scalar_t__ ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct wpa_driver_scan_params*) ; 

void wpa_scan_free_params(struct wpa_driver_scan_params *params)
{
	size_t i;

	if (params == NULL)
		return;

	for (i = 0; i < params->num_ssids; i++)
		os_free((u8 *) params->ssids[i].ssid);
	os_free((u8 *) params->extra_ies);
	os_free(params->freqs);
	os_free(params->filter_ssids);
	os_free(params->sched_scan_plans);

	/*
	 * Note: params->mac_addr_mask points to same memory allocation and
	 * must not be freed separately.
	 */
	os_free((u8 *) params->mac_addr);

	os_free((u8 *) params->bssid);

	os_free(params);
}