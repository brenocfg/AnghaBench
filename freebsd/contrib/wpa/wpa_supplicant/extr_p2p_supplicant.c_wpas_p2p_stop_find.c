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
struct wpa_supplicant {TYPE_1__* global; } ;
struct TYPE_2__ {int /*<<< orphan*/  pending_group_iface_for_p2ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_p2p_remove_pending_group_interface (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_p2p_stop_find_oper (struct wpa_supplicant*) ; 

void wpas_p2p_stop_find(struct wpa_supplicant *wpa_s)
{
	wpas_p2p_stop_find_oper(wpa_s);
	if (!wpa_s->global->pending_group_iface_for_p2ps)
		wpas_p2p_remove_pending_group_interface(wpa_s);
}