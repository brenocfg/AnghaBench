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
struct wpa_supplicant {int assoc_freq; TYPE_1__* current_ssid; struct hostapd_iface* ifmsh; struct hostapd_iface* ap_iface; } ;
struct hostapd_iface {int /*<<< orphan*/ * bss; } ;
struct TYPE_2__ {int frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostapd_event_ch_switch (int /*<<< orphan*/ ,int,int,int,int,int,int,int) ; 

void wpas_ap_ch_switch(struct wpa_supplicant *wpa_s, int freq, int ht,
		       int offset, int width, int cf1, int cf2, int finished)
{
	struct hostapd_iface *iface = wpa_s->ap_iface;

	if (!iface)
		iface = wpa_s->ifmsh;
	if (!iface)
		return;
	wpa_s->assoc_freq = freq;
	if (wpa_s->current_ssid)
		wpa_s->current_ssid->frequency = freq;
	hostapd_event_ch_switch(iface->bss[0], freq, ht,
				offset, width, cf1, cf2, finished);
}