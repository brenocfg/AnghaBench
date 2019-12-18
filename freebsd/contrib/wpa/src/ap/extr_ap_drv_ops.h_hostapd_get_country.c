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
struct hostapd_data {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* get_country ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline int hostapd_get_country(struct hostapd_data *hapd, char *alpha2)
{
	if (hapd->driver == NULL || hapd->driver->get_country == NULL)
		return -1;
	return hapd->driver->get_country(hapd->drv_priv, alpha2);
}