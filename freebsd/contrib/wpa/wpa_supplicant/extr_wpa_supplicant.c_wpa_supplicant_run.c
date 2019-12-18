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
struct wpa_supplicant {scalar_t__ ctrl_iface; int /*<<< orphan*/  p2p_mgmt; struct wpa_supplicant* next; } ;
struct TYPE_2__ {scalar_t__ wait_for_monitor; int /*<<< orphan*/  pid_file; scalar_t__ daemonize; } ;
struct wpa_global {struct wpa_supplicant* ifaces; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_register_signal_reconfig (int /*<<< orphan*/ ,struct wpa_global*) ; 
 int /*<<< orphan*/  eloop_register_signal_terminate (int /*<<< orphan*/ ,struct wpa_global*) ; 
 int /*<<< orphan*/  eloop_run () ; 
 scalar_t__ eloop_sock_requeue () ; 
 int /*<<< orphan*/  wpa_supplicant_ctrl_iface_wait (scalar_t__) ; 
 scalar_t__ wpa_supplicant_daemon (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_supplicant_match_existing (struct wpa_global*) ; 
 int /*<<< orphan*/  wpa_supplicant_reconfig ; 
 int /*<<< orphan*/  wpa_supplicant_terminate ; 

int wpa_supplicant_run(struct wpa_global *global)
{
	struct wpa_supplicant *wpa_s;

	if (global->params.daemonize &&
	    (wpa_supplicant_daemon(global->params.pid_file) ||
	     eloop_sock_requeue()))
		return -1;

#ifdef CONFIG_MATCH_IFACE
	if (wpa_supplicant_match_existing(global))
		return -1;
#endif

	if (global->params.wait_for_monitor) {
		for (wpa_s = global->ifaces; wpa_s; wpa_s = wpa_s->next)
			if (wpa_s->ctrl_iface && !wpa_s->p2p_mgmt)
				wpa_supplicant_ctrl_iface_wait(
					wpa_s->ctrl_iface);
	}

	eloop_register_signal_terminate(wpa_supplicant_terminate, global);
	eloop_register_signal_reconfig(wpa_supplicant_reconfig, global);

	eloop_run();

	return 0;
}