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
struct hostapd_data {TYPE_3__* conf; TYPE_2__* iface; } ;
struct TYPE_6__ {int /*<<< orphan*/  iface; } ;
struct TYPE_5__ {TYPE_1__* interfaces; } ;
struct TYPE_4__ {scalar_t__ (* ctrl_iface_init ) (struct hostapd_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ stub1 (struct hostapd_data*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_ctrl_iface_bss(struct hostapd_data *hapd)
{
	if (!hapd->iface->interfaces ||
	    !hapd->iface->interfaces->ctrl_iface_init)
		return 0;

	if (hapd->iface->interfaces->ctrl_iface_init(hapd)) {
		wpa_printf(MSG_ERROR,
			   "Failed to setup control interface for %s",
			   hapd->conf->iface);
		return -1;
	}

	return 0;
}