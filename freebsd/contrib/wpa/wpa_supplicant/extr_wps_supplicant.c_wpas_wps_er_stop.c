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
struct wpa_supplicant {int /*<<< orphan*/ * wps_er; } ;

/* Variables and functions */
 int /*<<< orphan*/  wps_er_deinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void wpas_wps_er_stop(struct wpa_supplicant *wpa_s)
{
#ifdef CONFIG_WPS_ER
	wps_er_deinit(wpa_s->wps_er, NULL, NULL);
	wpa_s->wps_er = NULL;
#endif /* CONFIG_WPS_ER */
}