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

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hs20_continue_icon_fetch ; 
 int /*<<< orphan*/  hs20_osu_icon_fetch_result (struct wpa_supplicant*,int) ; 

void hs20_icon_fetch_failed(struct wpa_supplicant *wpa_s)
{
	hs20_osu_icon_fetch_result(wpa_s, -1);
	eloop_cancel_timeout(hs20_continue_icon_fetch, wpa_s, NULL);
	eloop_register_timeout(0, 0, hs20_continue_icon_fetch, wpa_s, NULL);
}