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
typedef  int /*<<< orphan*/  u8 ;
struct prune_data {int /*<<< orphan*/  const* addr; struct hostapd_data* hapd; } ;
struct hostapd_data {TYPE_1__* iface; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* for_each_interface ) (TYPE_2__*,int /*<<< orphan*/ ,struct prune_data*) ;} ;
struct TYPE_3__ {TYPE_2__* interfaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  prune_associations ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,struct prune_data*) ; 

void hostapd_prune_associations(struct hostapd_data *hapd, const u8 *addr)
{
	struct prune_data data;
	data.hapd = hapd;
	data.addr = addr;
	if (hapd->iface->interfaces &&
	    hapd->iface->interfaces->for_each_interface)
		hapd->iface->interfaces->for_each_interface(
			hapd->iface->interfaces, prune_associations, &data);
}