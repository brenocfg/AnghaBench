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
struct wpa_supplicant {scalar_t__ p2p_scan_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  P2P_EVENT_FIND_STOPPED ; 
 int /*<<< orphan*/  wpa_msg_global (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpas_abort_ongoing_scan (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_notify_p2p_find_stopped (struct wpa_supplicant*) ; 

__attribute__((used)) static void wpas_find_stopped(void *ctx)
{
	struct wpa_supplicant *wpa_s = ctx;

	if (wpa_s->p2p_scan_work && wpas_abort_ongoing_scan(wpa_s) < 0)
		wpa_printf(MSG_DEBUG, "P2P: Abort ongoing scan failed");

	wpa_msg_global(wpa_s, MSG_INFO, P2P_EVENT_FIND_STOPPED);
	wpas_notify_p2p_find_stopped(wpa_s);
}