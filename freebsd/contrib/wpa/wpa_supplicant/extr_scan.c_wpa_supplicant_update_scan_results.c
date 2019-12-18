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
struct wpa_scan_results {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_scan_results_free (struct wpa_scan_results*) ; 
 struct wpa_scan_results* wpa_supplicant_get_scan_results (struct wpa_supplicant*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int wpa_supplicant_update_scan_results(struct wpa_supplicant *wpa_s)
{
	struct wpa_scan_results *scan_res;
	scan_res = wpa_supplicant_get_scan_results(wpa_s, NULL, 0);
	if (scan_res == NULL)
		return -1;
	wpa_scan_results_free(scan_res);

	return 0;
}