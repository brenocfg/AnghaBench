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
struct wpa_supplicant {scalar_t__ fetch_osu_icon_in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  hs20_next_osu_icon (struct wpa_supplicant*) ; 

__attribute__((used)) static void hs20_continue_icon_fetch(void *eloop_ctx, void *sock_ctx)
{
	struct wpa_supplicant *wpa_s = eloop_ctx;
	if (wpa_s->fetch_osu_icon_in_progress)
		hs20_next_osu_icon(wpa_s);
}