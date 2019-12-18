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
struct wpa_supplicant {int sched_scan_stop_req; scalar_t__ wpa_state; scalar_t__ pno_sched_pending; scalar_t__ pno; } ;

/* Variables and functions */
 scalar_t__ WPA_SCANNING ; 
 int /*<<< orphan*/  wpa_supplicant_req_scan (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wpa_supplicant_stop_sched_scan (struct wpa_supplicant*) ; 

int wpas_stop_pno(struct wpa_supplicant *wpa_s)
{
	int ret = 0;

	if (!wpa_s->pno)
		return 0;

	ret = wpa_supplicant_stop_sched_scan(wpa_s);
	wpa_s->sched_scan_stop_req = 1;

	wpa_s->pno = 0;
	wpa_s->pno_sched_pending = 0;

	if (wpa_s->wpa_state == WPA_SCANNING)
		wpa_supplicant_req_scan(wpa_s, 0, 0);

	return ret;
}