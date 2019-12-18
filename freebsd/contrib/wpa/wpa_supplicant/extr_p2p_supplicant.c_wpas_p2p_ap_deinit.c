#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {TYPE_2__* ap_iface; } ;
struct TYPE_4__ {TYPE_1__** bss; } ;
struct TYPE_3__ {int /*<<< orphan*/ * p2p_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_p2p_group_deinit (struct wpa_supplicant*) ; 

void wpas_p2p_ap_deinit(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->ap_iface->bss)
		wpa_s->ap_iface->bss[0]->p2p_group = NULL;
	wpas_p2p_group_deinit(wpa_s);
}