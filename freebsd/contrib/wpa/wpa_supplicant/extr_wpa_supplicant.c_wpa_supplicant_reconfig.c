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
struct wpa_supplicant {struct wpa_supplicant* next; } ;
struct wpa_global {struct wpa_supplicant* ifaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ wpa_debug_reopen_file () ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpa_supplicant_reload_configuration (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_terminate_proc (struct wpa_global*) ; 

__attribute__((used)) static void wpa_supplicant_reconfig(int sig, void *signal_ctx)
{
	struct wpa_global *global = signal_ctx;
	struct wpa_supplicant *wpa_s;
	for (wpa_s = global->ifaces; wpa_s; wpa_s = wpa_s->next) {
		wpa_dbg(wpa_s, MSG_DEBUG, "Signal %d received - reconfiguring",
			sig);
		if (wpa_supplicant_reload_configuration(wpa_s) < 0) {
			wpa_supplicant_terminate_proc(global);
		}
	}

	if (wpa_debug_reopen_file() < 0) {
		/* Ignore errors since we cannot really do much to fix this */
		wpa_printf(MSG_DEBUG, "Could not reopen debug log file");
	}
}