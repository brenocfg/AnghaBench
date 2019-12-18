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
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  EVENT_DISASSOC ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void wpa_driver_ndis_event_disconnect(struct wpa_driver_ndis_data *drv)
{
	wpa_printf(MSG_DEBUG, "NDIS: Media Disconnect Event");
	os_memset(drv->bssid, 0, ETH_ALEN);
	wpa_supplicant_event(drv->ctx, EVENT_DISASSOC, NULL);
}