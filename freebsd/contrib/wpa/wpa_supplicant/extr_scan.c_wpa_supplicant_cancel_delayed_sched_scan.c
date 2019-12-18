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
struct wpa_supplicant {int /*<<< orphan*/  sched_scan_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_delayed_sched_scan_timeout ; 

void wpa_supplicant_cancel_delayed_sched_scan(struct wpa_supplicant *wpa_s)
{
	if (!wpa_s->sched_scan_supported)
		return;

	wpa_dbg(wpa_s, MSG_DEBUG, "Cancelling delayed sched scan");
	eloop_cancel_timeout(wpa_supplicant_delayed_sched_scan_timeout,
			     wpa_s, NULL);
}