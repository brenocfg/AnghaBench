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
struct hostapd_data {int /*<<< orphan*/ * full_dynamic_vlan; TYPE_1__* conf; } ;
struct TYPE_2__ {int /*<<< orphan*/  vlan; } ;

/* Variables and functions */
 int /*<<< orphan*/  full_dynamic_vlan_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_dynamic_remove (struct hostapd_data*,int /*<<< orphan*/ ) ; 

void vlan_deinit(struct hostapd_data *hapd)
{
	vlan_dynamic_remove(hapd, hapd->conf->vlan);

#ifdef CONFIG_FULL_DYNAMIC_VLAN
	full_dynamic_vlan_deinit(hapd->full_dynamic_vlan);
	hapd->full_dynamic_vlan = NULL;
#endif /* CONFIG_FULL_DYNAMIC_VLAN */
}