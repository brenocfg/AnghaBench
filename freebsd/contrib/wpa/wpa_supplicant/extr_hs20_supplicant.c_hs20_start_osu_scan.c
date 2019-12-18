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
struct wpa_supplicant {int fetch_osu_waiting_scan; int /*<<< orphan*/  scan_res_handler; int /*<<< orphan*/  scan_req; int /*<<< orphan*/  num_osu_scans; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANUAL_SCAN_REQ ; 
 int /*<<< orphan*/  hs20_osu_scan_res_handler ; 
 int /*<<< orphan*/  wpa_supplicant_req_scan (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hs20_start_osu_scan(struct wpa_supplicant *wpa_s)
{
	wpa_s->fetch_osu_waiting_scan = 1;
	wpa_s->num_osu_scans++;
	wpa_s->scan_req = MANUAL_SCAN_REQ;
	wpa_s->scan_res_handler = hs20_osu_scan_res_handler;
	wpa_supplicant_req_scan(wpa_s, 0, 0);
}