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
struct wpa_supplicant {scalar_t__ fetch_anqp_in_progress; } ;

/* Variables and functions */

void interworking_stop_fetch_anqp(struct wpa_supplicant *wpa_s)
{
	if (!wpa_s->fetch_anqp_in_progress)
		return;

	wpa_s->fetch_anqp_in_progress = 0;
}