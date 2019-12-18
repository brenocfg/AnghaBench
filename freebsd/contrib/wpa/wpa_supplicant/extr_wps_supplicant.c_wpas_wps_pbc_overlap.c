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
struct TYPE_2__ {int /*<<< orphan*/  error_indication; int /*<<< orphan*/  config_error; } ;
union wps_event_data {TYPE_1__ fail; } ;
struct wpa_supplicant {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  WPS_CFG_MULTIPLE_PBC_DETECTED ; 
 int /*<<< orphan*/  WPS_EI_NO_ERROR ; 
 int /*<<< orphan*/  os_memset (union wps_event_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpas_notify_wps_event_fail (struct wpa_supplicant*,TYPE_1__*) ; 

void wpas_wps_pbc_overlap(struct wpa_supplicant *wpa_s)
{
	union wps_event_data data;

	os_memset(&data, 0, sizeof(data));
	data.fail.config_error = WPS_CFG_MULTIPLE_PBC_DETECTED;
	data.fail.error_indication = WPS_EI_NO_ERROR;
	/*
	 * Call wpas_notify_wps_event_fail() directly instead of through
	 * wpa_supplicant_wps_event() which would end up registering unnecessary
	 * timeouts (those are only for the case where the failure happens
	 * during an EAP-WSC exchange).
	 */
	wpas_notify_wps_event_fail(wpa_s, &data.fail);
}