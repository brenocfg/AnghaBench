#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hapd_interfaces {size_t count; TYPE_3__** iface; } ;
struct TYPE_6__ {size_t num_bss; TYPE_2__** bss; } ;
struct TYPE_5__ {TYPE_1__* conf; } ;
struct TYPE_4__ {scalar_t__ tnc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  eloop_run () ; 
 scalar_t__ eloop_sock_requeue () ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ os_daemonize (char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ tncs_global_init () ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int hostapd_global_run(struct hapd_interfaces *ifaces, int daemonize,
			      const char *pid_file)
{
#ifdef EAP_SERVER_TNC
	int tnc = 0;
	size_t i, k;

	for (i = 0; !tnc && i < ifaces->count; i++) {
		for (k = 0; k < ifaces->iface[i]->num_bss; k++) {
			if (ifaces->iface[i]->bss[0]->conf->tnc) {
				tnc++;
				break;
			}
		}
	}

	if (tnc && tncs_global_init() < 0) {
		wpa_printf(MSG_ERROR, "Failed to initialize TNCS");
		return -1;
	}
#endif /* EAP_SERVER_TNC */

	if (daemonize) {
		if (os_daemonize(pid_file)) {
			wpa_printf(MSG_ERROR, "daemon: %s", strerror(errno));
			return -1;
		}
		if (eloop_sock_requeue()) {
			wpa_printf(MSG_ERROR, "eloop_sock_requeue: %s",
				   strerror(errno));
			return -1;
		}
	}

	eloop_run();

	return 0;
}