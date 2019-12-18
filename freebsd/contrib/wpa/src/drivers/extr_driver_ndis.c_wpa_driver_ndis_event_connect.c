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
struct wpa_driver_ndis_data {int /*<<< orphan*/  ctx; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_ASSOC ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_driver_ndis_get_associnfo (struct wpa_driver_ndis_data*) ; 
 scalar_t__ wpa_driver_ndis_get_bssid (struct wpa_driver_ndis_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void wpa_driver_ndis_event_connect(struct wpa_driver_ndis_data *drv)
{
	wpa_printf(MSG_DEBUG, "NDIS: Media Connect Event");
	if (wpa_driver_ndis_get_bssid(drv, drv->bssid) == 0) {
		wpa_driver_ndis_get_associnfo(drv);
		wpa_supplicant_event(drv->ctx, EVENT_ASSOC, NULL);
	}
}