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
typedef  enum drv_br_net_param { ____Placeholder_drv_br_net_param } drv_br_net_param ;
struct TYPE_2__ {int (* br_set_net_param ) (int /*<<< orphan*/ *,int,unsigned int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,int,unsigned int) ; 

__attribute__((used)) static inline int hostapd_drv_br_set_net_param(struct hostapd_data *hapd,
					       enum drv_br_net_param param,
					       unsigned int val)
{
	if (hapd->driver == NULL || hapd->drv_priv == NULL ||
	    hapd->driver->br_set_net_param == NULL)
		return -1;
	return hapd->driver->br_set_net_param(hapd->drv_priv, param, val);
}