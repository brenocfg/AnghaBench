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
struct wpa_supplicant {int /*<<< orphan*/ * wps_er; int /*<<< orphan*/  ifname; int /*<<< orphan*/  wps; } ;

/* Variables and functions */
 int /*<<< orphan*/ * wps_er_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  wps_er_refresh (int /*<<< orphan*/ *) ; 

int wpas_wps_er_start(struct wpa_supplicant *wpa_s, const char *filter)
{
#ifdef CONFIG_WPS_ER
	if (wpa_s->wps_er) {
		wps_er_refresh(wpa_s->wps_er);
		return 0;
	}
	wpa_s->wps_er = wps_er_init(wpa_s->wps, wpa_s->ifname, filter);
	if (wpa_s->wps_er == NULL)
		return -1;
	return 0;
#else /* CONFIG_WPS_ER */
	return 0;
#endif /* CONFIG_WPS_ER */
}