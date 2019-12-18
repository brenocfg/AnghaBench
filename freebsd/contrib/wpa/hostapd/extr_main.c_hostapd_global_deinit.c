#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * drv_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* global_deinit ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  closelog () ; 
 int /*<<< orphan*/  eap_server_unregister_methods () ; 
 int /*<<< orphan*/  eloop_destroy () ; 
 TYPE_2__ global ; 
 int /*<<< orphan*/  os_daemonize_terminate (char const*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_deinit () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tncs_global_deinit () ; 
 TYPE_1__** wpa_drivers ; 

__attribute__((used)) static void hostapd_global_deinit(const char *pid_file, int eloop_initialized)
{
	int i;

	for (i = 0; wpa_drivers[i] && global.drv_priv; i++) {
		if (!global.drv_priv[i])
			continue;
		wpa_drivers[i]->global_deinit(global.drv_priv[i]);
	}
	os_free(global.drv_priv);
	global.drv_priv = NULL;

#ifdef EAP_SERVER_TNC
	tncs_global_deinit();
#endif /* EAP_SERVER_TNC */

	random_deinit();

	if (eloop_initialized)
		eloop_destroy();

#ifndef CONFIG_NATIVE_WINDOWS
	closelog();
#endif /* CONFIG_NATIVE_WINDOWS */

	eap_server_unregister_methods();

	os_daemonize_terminate(pid_file);
}