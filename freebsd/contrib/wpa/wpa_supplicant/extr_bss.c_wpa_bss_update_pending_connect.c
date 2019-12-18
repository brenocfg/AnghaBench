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
struct wpa_radio_work {struct wpa_connect_work* ctx; } ;
struct wpa_connect_work {int bss_removed; struct wpa_bss* bss; } ;
struct wpa_bss {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct wpa_radio_work* radio_work_pending (struct wpa_supplicant*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wpa_bss_update_pending_connect(struct wpa_supplicant *wpa_s,
					   struct wpa_bss *old_bss,
					   struct wpa_bss *new_bss)
{
	struct wpa_radio_work *work;
	struct wpa_connect_work *cwork;

	work = radio_work_pending(wpa_s, "sme-connect");
	if (!work)
		work = radio_work_pending(wpa_s, "connect");
	if (!work)
		return;

	cwork = work->ctx;
	if (cwork->bss != old_bss)
		return;

	wpa_printf(MSG_DEBUG,
		   "Update BSS pointer for the pending connect radio work");
	cwork->bss = new_bss;
	if (!new_bss)
		cwork->bss_removed = 1;
}