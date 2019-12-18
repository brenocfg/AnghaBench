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
struct hostapd_data {int /*<<< orphan*/ * drv_priv; TYPE_1__* driver; } ;
typedef  enum drv_br_port_attr { ____Placeholder_drv_br_port_attr } drv_br_port_attr ;
struct TYPE_2__ {int (* br_port_set_attr ) (int /*<<< orphan*/ *,int,unsigned int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,int,unsigned int) ; 

__attribute__((used)) static inline int hostapd_drv_br_port_set_attr(struct hostapd_data *hapd,
					       enum drv_br_port_attr attr,
					       unsigned int val)
{
	if (hapd->driver == NULL || hapd->drv_priv == NULL ||
	    hapd->driver->br_port_set_attr == NULL)
		return -1;
	return hapd->driver->br_port_set_attr(hapd->drv_priv, attr, val);
}