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
struct wpa_supplicant {int sched_scan_timed_out; int /*<<< orphan*/ * prev_sched_ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_supplicant_cancel_sched_scan (struct wpa_supplicant*) ; 

void wpas_scan_restart_sched_scan(struct wpa_supplicant *wpa_s)
{
	/* simulate timeout to restart the sched scan */
	wpa_s->sched_scan_timed_out = 1;
	wpa_s->prev_sched_ssid = NULL;
	wpa_supplicant_cancel_sched_scan(wpa_s);
}