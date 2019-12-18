#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hostapd_iface {size_t num_bss; TYPE_2__** bss; TYPE_1__* interfaces; TYPE_4__* conf; } ;
struct TYPE_8__ {TYPE_3__** bss; } ;
struct TYPE_7__ {int /*<<< orphan*/  iface; } ;
struct TYPE_6__ {int /*<<< orphan*/ * drv_priv; int /*<<< orphan*/  driver; } ;
struct TYPE_5__ {scalar_t__ (* driver_init ) (struct hostapd_iface*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ hostapd_config_check (TYPE_4__*,int) ; 
 int /*<<< orphan*/  hostapd_deinit_driver (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct hostapd_iface*) ; 
 int /*<<< orphan*/  hostapd_set_security_params (TYPE_3__*,int) ; 
 scalar_t__ hostapd_setup_interface (struct hostapd_iface*) ; 
 scalar_t__ stub1 (struct hostapd_iface*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int hostapd_enable_iface(struct hostapd_iface *hapd_iface)
{
	size_t j;

	if (hapd_iface->bss[0]->drv_priv != NULL) {
		wpa_printf(MSG_ERROR, "Interface %s already enabled",
			   hapd_iface->conf->bss[0]->iface);
		return -1;
	}

	wpa_printf(MSG_DEBUG, "Enable interface %s",
		   hapd_iface->conf->bss[0]->iface);

	for (j = 0; j < hapd_iface->num_bss; j++)
		hostapd_set_security_params(hapd_iface->conf->bss[j], 1);
	if (hostapd_config_check(hapd_iface->conf, 1) < 0) {
		wpa_printf(MSG_INFO, "Invalid configuration - cannot enable");
		return -1;
	}

	if (hapd_iface->interfaces == NULL ||
	    hapd_iface->interfaces->driver_init == NULL ||
	    hapd_iface->interfaces->driver_init(hapd_iface))
		return -1;

	if (hostapd_setup_interface(hapd_iface)) {
		hostapd_deinit_driver(hapd_iface->bss[0]->driver,
				      hapd_iface->bss[0]->drv_priv,
				      hapd_iface);
		return -1;
	}

	return 0;
}