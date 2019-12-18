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
struct wpa_supplicant {int /*<<< orphan*/  fetch_osu_icon_in_progress; } ;

/* Variables and functions */
 scalar_t__ eloop_is_timeout_registered (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hs20_continue_icon_fetch ; 
 int /*<<< orphan*/  hs20_icon_fetch_failed (struct wpa_supplicant*) ; 

void hs20_notify_parse_done(struct wpa_supplicant *wpa_s)
{
	if (!wpa_s->fetch_osu_icon_in_progress)
		return;
	if (eloop_is_timeout_registered(hs20_continue_icon_fetch, wpa_s, NULL))
		return;
	/*
	 * We are going through icon fetch, but no icon response was received.
	 * Assume this means the current AP could not provide an answer to avoid
	 * getting stuck in fetch iteration.
	 */
	hs20_icon_fetch_failed(wpa_s);
}