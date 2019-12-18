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
struct wpa_supplicant {int fetch_all_anqp; scalar_t__ fetch_osu_info; scalar_t__ network_select; scalar_t__ fetch_anqp_in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  interworking_start_fetch_anqp (struct wpa_supplicant*) ; 

int interworking_fetch_anqp(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->fetch_anqp_in_progress || wpa_s->network_select)
		return 0;

	wpa_s->network_select = 0;
	wpa_s->fetch_all_anqp = 1;
	wpa_s->fetch_osu_info = 0;

	interworking_start_fetch_anqp(wpa_s);

	return 0;
}