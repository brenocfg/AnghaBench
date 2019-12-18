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
struct wpa_supplicant {size_t last_scan_res_used; int /*<<< orphan*/ * last_scan_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 scalar_t__ wpas_add_beacon_rep (struct wpa_supplicant*,struct wpabuf**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_beacon_rep_no_results (struct wpa_supplicant*,struct wpabuf**) ; 

__attribute__((used)) static void wpas_beacon_rep_table(struct wpa_supplicant *wpa_s,
				  struct wpabuf **buf)
{
	size_t i;

	for (i = 0; i < wpa_s->last_scan_res_used; i++) {
		if (wpas_add_beacon_rep(wpa_s, buf, wpa_s->last_scan_res[i],
					0, 0) < 0)
			break;
	}

	if (!(*buf))
		wpas_beacon_rep_no_results(wpa_s, buf);

	wpa_hexdump_buf(MSG_DEBUG, "RRM: Radio Measurement report", *buf);
}