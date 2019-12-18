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
struct wpa_supplicant {TYPE_1__* global; scalar_t__ p2p_mgmt; } ;
struct wpa_ssid {int /*<<< orphan*/  p2p_group; } ;
struct TYPE_2__ {struct wpa_supplicant* p2p_group_formation; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_dbus_register_network (struct wpa_supplicant*,struct wpa_ssid*) ; 

void wpas_notify_network_added(struct wpa_supplicant *wpa_s,
			       struct wpa_ssid *ssid)
{
	if (wpa_s->p2p_mgmt)
		return;

	/*
	 * Networks objects created during any P2P activities should not be
	 * exposed out. They might/will confuse certain non-P2P aware
	 * applications since these network objects won't behave like
	 * regular ones.
	 */
	if (!ssid->p2p_group && wpa_s->global->p2p_group_formation != wpa_s)
		wpas_dbus_register_network(wpa_s, ssid);
}