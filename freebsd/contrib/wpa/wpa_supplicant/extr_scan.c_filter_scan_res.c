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
struct wpa_supplicant {int /*<<< orphan*/ * bssid_filter; } ;
struct wpa_scan_results {size_t num; TYPE_1__** res; } ;
struct TYPE_2__ {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_free (TYPE_1__*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ wpa_supplicant_filter_bssid_match (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

void filter_scan_res(struct wpa_supplicant *wpa_s,
		     struct wpa_scan_results *res)
{
	size_t i, j;

	if (wpa_s->bssid_filter == NULL)
		return;

	for (i = 0, j = 0; i < res->num; i++) {
		if (wpa_supplicant_filter_bssid_match(wpa_s,
						      res->res[i]->bssid)) {
			res->res[j++] = res->res[i];
		} else {
			os_free(res->res[i]);
			res->res[i] = NULL;
		}
	}

	if (res->num != j) {
		wpa_printf(MSG_DEBUG, "Filtered out %d scan results",
			   (int) (res->num - j));
		res->num = j;
	}
}