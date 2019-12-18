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
struct wpa_supplicant {struct wpa_supplicant* next; } ;
struct wpa_global {struct wpa_supplicant* ifaces; int /*<<< orphan*/  suspend_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_get_time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_drv_suspend (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

void wpas_notify_suspend(struct wpa_global *global)
{
	struct wpa_supplicant *wpa_s;

	os_get_time(&global->suspend_time);
	wpa_printf(MSG_DEBUG, "System suspend notification");
	for (wpa_s = global->ifaces; wpa_s; wpa_s = wpa_s->next)
		wpa_drv_suspend(wpa_s);
}