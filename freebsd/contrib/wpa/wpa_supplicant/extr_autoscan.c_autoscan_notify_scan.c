#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {int scan_interval; TYPE_2__* sched_scan_plans; scalar_t__ autoscan_priv; TYPE_1__* autoscan; } ;
struct wpa_scan_results {int dummy; } ;
struct TYPE_4__ {int interval; } ;
struct TYPE_3__ {int (* notify_scan ) (scalar_t__,struct wpa_scan_results*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  request_scan (struct wpa_supplicant*) ; 
 int stub1 (scalar_t__,struct wpa_scan_results*) ; 

int autoscan_notify_scan(struct wpa_supplicant *wpa_s,
			 struct wpa_scan_results *scan_res)
{
	int interval;

	if (wpa_s->autoscan && wpa_s->autoscan_priv) {
		interval = wpa_s->autoscan->notify_scan(wpa_s->autoscan_priv,
							scan_res);

		if (interval <= 0)
			return -1;

		wpa_s->scan_interval = interval;
		wpa_s->sched_scan_plans[0].interval = interval;

		request_scan(wpa_s);
	}

	return 0;
}