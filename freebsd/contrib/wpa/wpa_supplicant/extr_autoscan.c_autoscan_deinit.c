#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {int scan_interval; scalar_t__ sched_scan_plans_num; int /*<<< orphan*/ * sched_scan_plans; int /*<<< orphan*/ * autoscan_priv; TYPE_1__* autoscan; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* deinit ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void autoscan_deinit(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->autoscan && wpa_s->autoscan_priv) {
		wpa_printf(MSG_DEBUG, "autoscan: Deinitializing module '%s'",
			   wpa_s->autoscan->name);
		wpa_s->autoscan->deinit(wpa_s->autoscan_priv);
		wpa_s->autoscan = NULL;
		wpa_s->autoscan_priv = NULL;

		wpa_s->scan_interval = 5;

		os_free(wpa_s->sched_scan_plans);
		wpa_s->sched_scan_plans = NULL;
		wpa_s->sched_scan_plans_num = 0;
	}
}