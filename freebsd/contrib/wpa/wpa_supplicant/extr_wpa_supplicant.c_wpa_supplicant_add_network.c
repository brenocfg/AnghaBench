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
struct wpa_supplicant {int /*<<< orphan*/  conf; } ;
struct wpa_ssid {int disabled; } ;

/* Variables and functions */
 struct wpa_ssid* wpa_config_add_network (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_config_set_network_defaults (struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpas_notify_network_added (struct wpa_supplicant*,struct wpa_ssid*) ; 

struct wpa_ssid * wpa_supplicant_add_network(struct wpa_supplicant *wpa_s)
{
	struct wpa_ssid *ssid;

	ssid = wpa_config_add_network(wpa_s->conf);
	if (!ssid)
		return NULL;
	wpas_notify_network_added(wpa_s, ssid);
	ssid->disabled = 1;
	wpa_config_set_network_defaults(ssid);

	return ssid;
}