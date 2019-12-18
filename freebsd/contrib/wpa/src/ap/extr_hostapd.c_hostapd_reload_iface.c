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
struct hostapd_iface {size_t num_bss; int /*<<< orphan*/ * bss; TYPE_2__* conf; } ;
struct TYPE_4__ {TYPE_1__** bss; } ;
struct TYPE_3__ {int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  hostapd_clear_old (struct hostapd_iface*) ; 
 scalar_t__ hostapd_config_check (TYPE_2__*,int) ; 
 int /*<<< orphan*/  hostapd_reload_bss (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_set_security_params (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int hostapd_reload_iface(struct hostapd_iface *hapd_iface)
{
	size_t j;

	wpa_printf(MSG_DEBUG, "Reload interface %s",
		   hapd_iface->conf->bss[0]->iface);
	for (j = 0; j < hapd_iface->num_bss; j++)
		hostapd_set_security_params(hapd_iface->conf->bss[j], 1);
	if (hostapd_config_check(hapd_iface->conf, 1) < 0) {
		wpa_printf(MSG_ERROR, "Updated configuration is invalid");
		return -1;
	}
	hostapd_clear_old(hapd_iface);
	for (j = 0; j < hapd_iface->num_bss; j++)
		hostapd_reload_bss(hapd_iface->bss[j]);

	return 0;
}