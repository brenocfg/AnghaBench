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
struct wpa_supplicant {struct wpa_bss* current_bss; int /*<<< orphan*/  bssid; } ;
struct wpa_bss {int dummy; } ;

/* Variables and functions */
 struct wpa_bss* wpa_supplicant_get_new_bss (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_update_scan_results (struct wpa_supplicant*) ; 

__attribute__((used)) static void wpa_supplicant_update_current_bss(struct wpa_supplicant *wpa_s)
{
	struct wpa_bss *bss = wpa_supplicant_get_new_bss(wpa_s, wpa_s->bssid);

	if (!bss) {
		wpa_supplicant_update_scan_results(wpa_s);

		/* Get the BSS from the new scan results */
		bss = wpa_supplicant_get_new_bss(wpa_s, wpa_s->bssid);
	}

	if (bss)
		wpa_s->current_bss = bss;
}