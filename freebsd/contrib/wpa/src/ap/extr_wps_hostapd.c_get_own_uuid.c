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
typedef  int /*<<< orphan*/  u8 ;
struct hostapd_iface {TYPE_1__* interfaces; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* for_each_interface ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  get_uuid_cb ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static const u8 * get_own_uuid(struct hostapd_iface *iface)
{
	const u8 *uuid;
	if (iface->interfaces == NULL ||
	    iface->interfaces->for_each_interface == NULL)
		return NULL;
	uuid = NULL;
	iface->interfaces->for_each_interface(iface->interfaces, get_uuid_cb,
					      &uuid);
	return uuid;
}