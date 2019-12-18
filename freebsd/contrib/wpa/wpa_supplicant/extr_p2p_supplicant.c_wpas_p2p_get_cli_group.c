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
struct wpa_supplicant {struct wpa_supplicant* next; TYPE_1__* global; } ;
struct TYPE_2__ {struct wpa_supplicant* ifaces; } ;

/* Variables and functions */
 scalar_t__ p2p_is_active_persistent_cli (struct wpa_supplicant*) ; 

__attribute__((used)) static struct wpa_supplicant *
wpas_p2p_get_cli_group(struct wpa_supplicant *wpa_s)
{
	for (wpa_s = wpa_s->global->ifaces; wpa_s; wpa_s = wpa_s->next) {
		if (p2p_is_active_persistent_cli(wpa_s))
			return wpa_s;
	}

	return NULL;
}