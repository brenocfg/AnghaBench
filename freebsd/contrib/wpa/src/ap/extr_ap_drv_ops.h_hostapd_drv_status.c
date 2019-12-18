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
struct TYPE_2__ {int (* status ) (int /*<<< orphan*/ ,char*,size_t) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static inline int hostapd_drv_status(struct hostapd_data *hapd, char *buf,
				     size_t buflen)
{
	if (!hapd->driver || !hapd->driver->status || !hapd->drv_priv)
		return -1;
	return hapd->driver->status(hapd->drv_priv, buf, buflen);
}