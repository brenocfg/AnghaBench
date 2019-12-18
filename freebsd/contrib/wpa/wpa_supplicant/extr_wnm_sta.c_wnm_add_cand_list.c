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
struct wpabuf {int dummy; } ;
struct wpa_supplicant {unsigned int last_scan_res_used; struct wpa_bss** last_scan_res; int /*<<< orphan*/  last_scan; struct wpa_ssid* current_ssid; } ;
struct wpa_ssid {int dummy; } ;
struct wpa_bss {int dummy; } ;
struct os_reltime {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_get_reltime (struct os_reltime*) ; 
 scalar_t__ os_reltime_expired (struct os_reltime*,int /*<<< orphan*/ *,int) ; 
 int wnm_nei_rep_add_bss (struct wpa_supplicant*,struct wpa_bss*,struct wpabuf**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpa_scan_res_match (struct wpa_supplicant*,unsigned int,struct wpa_bss*,struct wpa_ssid*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wnm_add_cand_list(struct wpa_supplicant *wpa_s, struct wpabuf **buf)
{
	unsigned int i, pref = 255;
	struct os_reltime now;
	struct wpa_ssid *ssid = wpa_s->current_ssid;

	if (!ssid)
		return;

	/*
	 * TODO: Define when scan results are no longer valid for the candidate
	 * list.
	 */
	os_get_reltime(&now);
	if (os_reltime_expired(&now, &wpa_s->last_scan, 10))
		return;

	wpa_printf(MSG_DEBUG,
		   "WNM: Add candidate list to BSS Transition Management Response frame");
	for (i = 0; i < wpa_s->last_scan_res_used && pref; i++) {
		struct wpa_bss *bss = wpa_s->last_scan_res[i];
		int res;

		if (wpa_scan_res_match(wpa_s, i, bss, ssid, 1, 0)) {
			res = wnm_nei_rep_add_bss(wpa_s, bss, buf, pref--);
			if (res == -2)
				continue; /* could not build entry for BSS */
			if (res < 0)
				break; /* no more room for candidates */
			if (pref == 1)
				break;
		}
	}

	wpa_hexdump_buf(MSG_DEBUG,
			"WNM: BSS Transition Management Response candidate list",
			*buf);
}