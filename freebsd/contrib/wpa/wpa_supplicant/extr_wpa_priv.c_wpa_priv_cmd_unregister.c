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
struct wpa_priv_interface {scalar_t__ wpas_registered; int /*<<< orphan*/ * drv_global_priv; TYPE_1__* driver; int /*<<< orphan*/ * drv_priv; } ;
struct sockaddr_un {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* global_deinit ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* deinit ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wpa_priv_cmd_unregister(struct wpa_priv_interface *iface,
				    struct sockaddr_un *from)
{
	if (iface->drv_priv) {
		if (iface->driver->deinit)
			iface->driver->deinit(iface->drv_priv);
		iface->drv_priv = NULL;
		if (iface->drv_global_priv) {
			iface->driver->global_deinit(iface->drv_global_priv);
			iface->drv_global_priv = NULL;
		}
		iface->wpas_registered = 0;
	}
}