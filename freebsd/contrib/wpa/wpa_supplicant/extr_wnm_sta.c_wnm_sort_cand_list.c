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
struct wpa_supplicant {int /*<<< orphan*/  wnm_num_neighbor_report; int /*<<< orphan*/  wnm_neighbor_report_elements; } ;
struct neighbor_report {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cand_pref_compar ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wnm_sort_cand_list(struct wpa_supplicant *wpa_s)
{
	if (!wpa_s->wnm_neighbor_report_elements)
		return;
	qsort(wpa_s->wnm_neighbor_report_elements,
	      wpa_s->wnm_num_neighbor_report, sizeof(struct neighbor_report),
	      cand_pref_compar);
}