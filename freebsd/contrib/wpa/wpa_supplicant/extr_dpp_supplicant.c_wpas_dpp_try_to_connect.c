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
struct wpa_supplicant {int reassociate; scalar_t__ normal_scans; scalar_t__ scan_runs; scalar_t__ disconnected; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_cancel_sched_scan (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_req_scan (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpas_dpp_try_to_connect(struct wpa_supplicant *wpa_s)
{
	wpa_printf(MSG_DEBUG, "DPP: Trying to connect to the new network");
	wpa_s->disconnected = 0;
	wpa_s->reassociate = 1;
	wpa_s->scan_runs = 0;
	wpa_s->normal_scans = 0;
	wpa_supplicant_cancel_sched_scan(wpa_s);
	wpa_supplicant_req_scan(wpa_s, 0, 0);
}