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
struct external_auth {int dummy; } ;
struct TYPE_2__ {int (* send_external_auth_status ) (int /*<<< orphan*/ ,struct external_auth*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct external_auth*) ; 

__attribute__((used)) static inline int
hostapd_drv_send_external_auth_status(struct hostapd_data *hapd,
				      struct external_auth *params)
{
	if (!hapd->driver || !hapd->drv_priv ||
	    !hapd->driver->send_external_auth_status)
		return -1;
	return hapd->driver->send_external_auth_status(hapd->drv_priv, params);
}