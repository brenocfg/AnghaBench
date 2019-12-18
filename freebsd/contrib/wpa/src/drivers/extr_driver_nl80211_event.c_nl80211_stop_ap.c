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
struct wpa_driver_nl80211_data {int /*<<< orphan*/  ctx; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_INTERFACE_UNAVAILABLE ; 
 int /*<<< orphan*/  wpa_supplicant_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nl80211_stop_ap(struct wpa_driver_nl80211_data *drv,
			    struct nlattr **tb)
{
	wpa_supplicant_event(drv->ctx, EVENT_INTERFACE_UNAVAILABLE, NULL);
}