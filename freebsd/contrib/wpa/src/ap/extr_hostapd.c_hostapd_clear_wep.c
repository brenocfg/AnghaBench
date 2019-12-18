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
struct hostapd_data {scalar_t__ conf; TYPE_1__* iface; scalar_t__ drv_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver_ap_teardown; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostapd_broadcast_wep_clear (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_set_privacy (struct hostapd_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostapd_clear_wep(struct hostapd_data *hapd)
{
	if (hapd->drv_priv && !hapd->iface->driver_ap_teardown && hapd->conf) {
		hostapd_set_privacy(hapd, 0);
		hostapd_broadcast_wep_clear(hapd);
	}
}