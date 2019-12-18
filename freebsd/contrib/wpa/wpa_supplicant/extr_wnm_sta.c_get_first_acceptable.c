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
struct wpa_supplicant {unsigned int wnm_num_neighbor_report; struct neighbor_report* wnm_neighbor_report_elements; } ;
struct wpa_bss {int dummy; } ;
struct neighbor_report {int /*<<< orphan*/  bssid; scalar_t__ acceptable; } ;

/* Variables and functions */
 struct wpa_bss* wpa_bss_get_bssid (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpa_bss * get_first_acceptable(struct wpa_supplicant *wpa_s)
{
	unsigned int i;
	struct neighbor_report *nei;

	for (i = 0; i < wpa_s->wnm_num_neighbor_report; i++) {
		nei = &wpa_s->wnm_neighbor_report_elements[i];
		if (nei->acceptable)
			return wpa_bss_get_bssid(wpa_s, nei->bssid);
	}

	return NULL;
}