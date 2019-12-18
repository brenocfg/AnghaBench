#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wpa_supplicant {scalar_t__ wpa_state; } ;

/* Variables and functions */
 scalar_t__ WPA_DISCONNECTED ; 
 scalar_t__ WPA_SCANNING ; 
 int /*<<< orphan*/  autoscan_deinit (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_start_autoscan (struct wpa_supplicant*) ; 

void wpa_supplicant_reinit_autoscan(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->wpa_state == WPA_DISCONNECTED ||
	    wpa_s->wpa_state == WPA_SCANNING) {
		autoscan_deinit(wpa_s);
		wpa_supplicant_start_autoscan(wpa_s);
	}
}