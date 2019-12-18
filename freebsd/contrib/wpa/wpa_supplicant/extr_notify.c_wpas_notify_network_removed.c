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
struct wpa_supplicant {int /*<<< orphan*/  p2p_mgmt; TYPE_1__* global; scalar_t__ wpa; struct wpa_ssid* next_ssid; } ;
struct wpa_ssid {int /*<<< orphan*/  id; int /*<<< orphan*/  p2p_group; } ;
struct TYPE_2__ {struct wpa_supplicant* p2p_group_formation; } ;

/* Variables and functions */
 scalar_t__ network_is_persistent_group (struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpa_sm_pmksa_cache_flush (scalar_t__,struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpas_dbus_unregister_network (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_notify_persistent_group_removed (struct wpa_supplicant*,struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpas_p2p_network_removed (struct wpa_supplicant*,struct wpa_ssid*) ; 

void wpas_notify_network_removed(struct wpa_supplicant *wpa_s,
				 struct wpa_ssid *ssid)
{
	if (wpa_s->next_ssid == ssid)
		wpa_s->next_ssid = NULL;
	if (wpa_s->wpa)
		wpa_sm_pmksa_cache_flush(wpa_s->wpa, ssid);
	if (!ssid->p2p_group && wpa_s->global->p2p_group_formation != wpa_s &&
	    !wpa_s->p2p_mgmt)
		wpas_dbus_unregister_network(wpa_s, ssid->id);
	if (network_is_persistent_group(ssid))
		wpas_notify_persistent_group_removed(wpa_s, ssid);

	wpas_p2p_network_removed(wpa_s, ssid);
}