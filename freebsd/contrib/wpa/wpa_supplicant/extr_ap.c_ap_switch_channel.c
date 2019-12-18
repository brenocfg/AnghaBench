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
struct wpa_supplicant {TYPE_1__* ap_iface; } ;
struct csa_settings {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bss; } ;

/* Variables and functions */
 int hostapd_switch_channel (int /*<<< orphan*/ ,struct csa_settings*) ; 

int ap_switch_channel(struct wpa_supplicant *wpa_s,
		      struct csa_settings *settings)
{
#ifdef NEED_AP_MLME
	if (!wpa_s->ap_iface || !wpa_s->ap_iface->bss[0])
		return -1;

	return hostapd_switch_channel(wpa_s->ap_iface->bss[0], settings);
#else /* NEED_AP_MLME */
	return -1;
#endif /* NEED_AP_MLME */
}