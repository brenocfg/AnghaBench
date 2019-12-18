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
struct wpa_supplicant {scalar_t__ wpa_state; TYPE_1__* conf; } ;
struct TYPE_2__ {int /*<<< orphan*/  preassoc_mac_addr; } ;

/* Variables and functions */
 scalar_t__ WPA_AUTHENTICATING ; 
 int wpas_update_random_addr (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

int wpas_update_random_addr_disassoc(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->wpa_state >= WPA_AUTHENTICATING ||
	    !wpa_s->conf->preassoc_mac_addr)
		return 0;

	return wpas_update_random_addr(wpa_s, wpa_s->conf->preassoc_mac_addr);
}