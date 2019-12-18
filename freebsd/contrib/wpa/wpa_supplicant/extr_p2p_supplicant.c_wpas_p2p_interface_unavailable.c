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
struct wpa_supplicant {TYPE_1__* current_ssid; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2p_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  P2P_GROUP_REMOVAL_UNAVAILABLE ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_p2p_group_delete (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

void wpas_p2p_interface_unavailable(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->current_ssid == NULL || !wpa_s->current_ssid->p2p_group)
		return;

	wpa_printf(MSG_DEBUG, "P2P: Remove group due to driver resource not "
		   "being available anymore");
	wpas_p2p_group_delete(wpa_s, P2P_GROUP_REMOVAL_UNAVAILABLE);
}