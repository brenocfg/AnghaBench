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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {TYPE_1__* ap_iface; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bss; } ;

/* Variables and functions */
 int hostapd_p2p_set_noa (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int wpas_p2p_set_noa(struct wpa_supplicant *wpa_s, u8 count, int start,
		     int duration)
{
	if (!wpa_s->ap_iface)
		return -1;
	return hostapd_p2p_set_noa(wpa_s->ap_iface->bss[0], count, start,
				   duration);
}