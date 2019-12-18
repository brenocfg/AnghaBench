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
struct TYPE_2__ {char const* (* get_radio_name ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 char const* stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline const char * hostapd_drv_get_radio_name(struct hostapd_data *hapd)
{
	if (hapd->driver == NULL || hapd->drv_priv == NULL ||
	    hapd->driver->get_radio_name == NULL)
		return NULL;
	return hapd->driver->get_radio_name(hapd->drv_priv);
}