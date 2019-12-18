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
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int eloop_is_timeout_registered (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpas_wps_reenable_networks_cb ; 

int wpas_wps_reenable_networks_pending(struct wpa_supplicant *wpa_s)
{
	return eloop_is_timeout_registered(wpas_wps_reenable_networks_cb,
					   wpa_s, NULL);
}