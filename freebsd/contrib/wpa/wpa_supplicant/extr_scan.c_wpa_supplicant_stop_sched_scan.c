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
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int wpa_drv_stop_sched_scan (struct wpa_supplicant*) ; 

__attribute__((used)) static int wpa_supplicant_stop_sched_scan(struct wpa_supplicant *wpa_s)
{
	int ret;

	ret = wpa_drv_stop_sched_scan(wpa_s);
	if (ret) {
		wpa_dbg(wpa_s, MSG_DEBUG, "stopping sched_scan failed!");
		/* TODO: what to do if stopping fails? */
		return -1;
	}

	return ret;
}