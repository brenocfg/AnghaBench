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
struct wpa_supplicant {TYPE_1__* conf; } ;
struct wpa_ssid {scalar_t__ disabled; struct wpa_ssid* next; } ;
struct TYPE_2__ {struct wpa_ssid* ssid; scalar_t__ cred; scalar_t__ interworking; scalar_t__ auto_interworking; } ;

/* Variables and functions */
 int wpas_temp_disabled (struct wpa_supplicant*,struct wpa_ssid*) ; 

__attribute__((used)) static int wpas_reenabled_network_time(struct wpa_supplicant *wpa_s)
{
	struct wpa_ssid *ssid;
	int disabled_for, res = 0;

#ifdef CONFIG_INTERWORKING
	if (wpa_s->conf->auto_interworking && wpa_s->conf->interworking &&
	    wpa_s->conf->cred)
		return 0;
#endif /* CONFIG_INTERWORKING */

	for (ssid = wpa_s->conf->ssid; ssid; ssid = ssid->next) {
		if (ssid->disabled)
			continue;

		disabled_for = wpas_temp_disabled(wpa_s, ssid);
		if (!disabled_for)
			return 0;

		if (!res || disabled_for < res)
			res = disabled_for;
	}

	return res;
}