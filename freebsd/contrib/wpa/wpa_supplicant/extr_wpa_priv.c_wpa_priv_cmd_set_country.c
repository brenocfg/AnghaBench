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
struct wpa_priv_interface {int /*<<< orphan*/ * drv_priv; TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_country ) (int /*<<< orphan*/ *,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void wpa_priv_cmd_set_country(struct wpa_priv_interface *iface,
				     char *buf)
{
	if (iface->drv_priv == NULL || iface->driver->set_country == NULL ||
	    *buf == '\0')
		return;

	iface->driver->set_country(iface->drv_priv, buf);
}