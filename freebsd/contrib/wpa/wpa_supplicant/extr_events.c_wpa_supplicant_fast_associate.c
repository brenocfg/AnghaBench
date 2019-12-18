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
struct wpa_supplicant {scalar_t__ last_scan_res_used; int /*<<< orphan*/  last_scan; scalar_t__ ignore_post_flush_scan_res; } ;
struct os_reltime {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_get_reltime (struct os_reltime*) ; 
 scalar_t__ os_reltime_expired (struct os_reltime*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int wpas_select_network_from_last_scan (struct wpa_supplicant*,int /*<<< orphan*/ ,int) ; 

int wpa_supplicant_fast_associate(struct wpa_supplicant *wpa_s)
{
#ifdef CONFIG_NO_SCAN_PROCESSING
	return -1;
#else /* CONFIG_NO_SCAN_PROCESSING */
	struct os_reltime now;

	wpa_s->ignore_post_flush_scan_res = 0;

	if (wpa_s->last_scan_res_used == 0)
		return -1;

	os_get_reltime(&now);
	if (os_reltime_expired(&now, &wpa_s->last_scan, 5)) {
		wpa_printf(MSG_DEBUG, "Fast associate: Old scan results");
		return -1;
	}

	return wpas_select_network_from_last_scan(wpa_s, 0, 1);
#endif /* CONFIG_NO_SCAN_PROCESSING */
}