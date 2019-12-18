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
struct hostapd_data {int /*<<< orphan*/ * drv_priv; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* br_add_ip_neigh ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline int hostapd_drv_br_add_ip_neigh(struct hostapd_data *hapd,
					      int version, const u8 *ipaddr,
					      int prefixlen, const u8 *addr)
{
	if (hapd->driver == NULL || hapd->drv_priv == NULL ||
	    hapd->driver->br_add_ip_neigh == NULL)
		return -1;
	return hapd->driver->br_add_ip_neigh(hapd->drv_priv, version, ipaddr,
					     prefixlen, addr);
}