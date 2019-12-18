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
struct wpa_supplicant {scalar_t__ wps_ap_iter; scalar_t__ num_wps_ap; int /*<<< orphan*/ * wps_ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wpas_wps_clear_ap_info(struct wpa_supplicant *wpa_s)
{
	os_free(wpa_s->wps_ap);
	wpa_s->wps_ap = NULL;
	wpa_s->num_wps_ap = 0;
	wpa_s->wps_ap_iter = 0;
}