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
struct TYPE_2__ {scalar_t__ next; } ;
struct wpa_supplicant {TYPE_1__ icon_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hs20_continue_icon_fetch ; 
 int /*<<< orphan*/  hs20_del_icon (struct wpa_supplicant*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hs20_free_osu_prov (struct wpa_supplicant*) ; 

void hs20_deinit(struct wpa_supplicant *wpa_s)
{
	eloop_cancel_timeout(hs20_continue_icon_fetch, wpa_s, NULL);
	hs20_free_osu_prov(wpa_s);
	if (wpa_s->icon_head.next)
		hs20_del_icon(wpa_s, NULL, NULL);
}