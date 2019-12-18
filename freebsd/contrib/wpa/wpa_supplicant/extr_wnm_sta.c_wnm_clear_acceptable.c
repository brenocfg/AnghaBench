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
struct wpa_supplicant {unsigned int wnm_num_neighbor_report; TYPE_1__* wnm_neighbor_report_elements; } ;
struct TYPE_2__ {scalar_t__ acceptable; } ;

/* Variables and functions */

__attribute__((used)) static void wnm_clear_acceptable(struct wpa_supplicant *wpa_s)
{
	unsigned int i;

	for (i = 0; i < wpa_s->wnm_num_neighbor_report; i++)
		wpa_s->wnm_neighbor_report_elements[i].acceptable = 0;
}