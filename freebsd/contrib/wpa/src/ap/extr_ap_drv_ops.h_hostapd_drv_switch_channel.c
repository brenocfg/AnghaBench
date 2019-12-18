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
struct csa_settings {int dummy; } ;
struct TYPE_2__ {int (* switch_channel ) (int /*<<< orphan*/ *,struct csa_settings*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct csa_settings*) ; 

__attribute__((used)) static inline int hostapd_drv_switch_channel(struct hostapd_data *hapd,
					     struct csa_settings *settings)
{
	if (hapd->driver == NULL || hapd->driver->switch_channel == NULL ||
	    hapd->drv_priv == NULL)
		return -1;

	return hapd->driver->switch_channel(hapd->drv_priv, settings);
}