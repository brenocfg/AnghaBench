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
struct hostapd_iface {size_t num_bss; TYPE_2__* interfaces; struct hostapd_data** bss; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_4__ {scalar_t__ (* ctrl_iface_init ) (struct hostapd_data*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ stub1 (struct hostapd_data*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_ctrl_iface(struct hostapd_iface *iface)
{
	size_t i;

	if (!iface->interfaces || !iface->interfaces->ctrl_iface_init)
		return 0;

	for (i = 0; i < iface->num_bss; i++) {
		struct hostapd_data *hapd = iface->bss[i];
		if (iface->interfaces->ctrl_iface_init(hapd)) {
			wpa_printf(MSG_ERROR,
				   "Failed to setup control interface for %s",
				   hapd->conf->iface);
			return -1;
		}
	}

	return 0;
}