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
struct hostapd_iface {int /*<<< orphan*/  extended_capa_len; int /*<<< orphan*/  extended_capa_mask; int /*<<< orphan*/  extended_capa; struct hostapd_data** bss; } ;
struct hostapd_data {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_ext_capab ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WPA_IF_AP_BSS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void hostapd_get_ext_capa(struct hostapd_iface *iface)
{
	struct hostapd_data *hapd = iface->bss[0];

	if (!hapd->driver || !hapd->driver->get_ext_capab)
		return;

	hapd->driver->get_ext_capab(hapd->drv_priv, WPA_IF_AP_BSS,
				    &iface->extended_capa,
				    &iface->extended_capa_mask,
				    &iface->extended_capa_len);
}