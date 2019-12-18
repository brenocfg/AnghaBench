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
struct hostapd_iface {int num_bss; struct hostapd_data** bss; } ;
struct hostapd_data {int /*<<< orphan*/  setup_complete_cb_ctx; int /*<<< orphan*/  (* setup_complete_cb ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostapd_interface_setup_failure_handler(void *eloop_ctx,
						    void *timeout_ctx)
{
	struct hostapd_iface *iface = eloop_ctx;
	struct hostapd_data *hapd;

	if (iface->num_bss < 1 || !iface->bss || !iface->bss[0])
		return;
	hapd = iface->bss[0];
	if (hapd->setup_complete_cb)
		hapd->setup_complete_cb(hapd->setup_complete_cb_ctx);
}