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
struct wpa_priv_interface {int wpas_registered; int /*<<< orphan*/ * drv_priv; TYPE_1__* driver; int /*<<< orphan*/  drv_addr_len; int /*<<< orphan*/  drv_addr; int /*<<< orphan*/  ifname; int /*<<< orphan*/  driver_name; int /*<<< orphan*/ * drv_global_priv; int /*<<< orphan*/  ctx; int /*<<< orphan*/ ** l2; } ;
struct sockaddr_un {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_2__ {scalar_t__ (* set_param ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* init ) (struct wpa_priv_interface*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * (* init2 ) (struct wpa_priv_interface*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* global_init ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* global_deinit ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* deinit ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int WPA_PRIV_MAX_L2 ; 
 int /*<<< orphan*/  l2_packet_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,struct sockaddr_un*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub4 (struct wpa_priv_interface*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub5 (struct wpa_priv_interface*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void wpa_priv_cmd_register(struct wpa_priv_interface *iface,
				  struct sockaddr_un *from, socklen_t fromlen)
{
	int i;

	if (iface->drv_priv) {
		wpa_printf(MSG_DEBUG, "Cleaning up forgotten driver instance");
		if (iface->driver->deinit)
			iface->driver->deinit(iface->drv_priv);
		iface->drv_priv = NULL;
		if (iface->drv_global_priv) {
			iface->driver->global_deinit(iface->drv_global_priv);
			iface->drv_global_priv = NULL;
		}
		iface->wpas_registered = 0;
	}

	for (i = 0; i < WPA_PRIV_MAX_L2; i++) {
		if (iface->l2[i]) {
			wpa_printf(MSG_DEBUG,
				   "Cleaning up forgotten l2_packet instance");
			l2_packet_deinit(iface->l2[i]);
			iface->l2[i] = NULL;
		}
	}

	if (iface->driver->init2) {
		if (iface->driver->global_init) {
			iface->drv_global_priv =
				iface->driver->global_init(iface->ctx);
			if (!iface->drv_global_priv) {
				wpa_printf(MSG_INFO,
					   "Failed to initialize driver global context");
				return;
			}
		} else {
			iface->drv_global_priv = NULL;
		}
		iface->drv_priv = iface->driver->init2(iface, iface->ifname,
						       iface->drv_global_priv);
	} else if (iface->driver->init) {
		iface->drv_priv = iface->driver->init(iface, iface->ifname);
	} else {
		return;
	}
	if (iface->drv_priv == NULL) {
		wpa_printf(MSG_DEBUG, "Failed to initialize driver wrapper");
		return;
	}

	wpa_printf(MSG_DEBUG, "Driver wrapper '%s' initialized for interface "
		   "'%s'", iface->driver_name, iface->ifname);

	os_memcpy(&iface->drv_addr, from, fromlen);
	iface->drv_addr_len = fromlen;
	iface->wpas_registered = 1;

	if (iface->driver->set_param &&
	    iface->driver->set_param(iface->drv_priv, NULL) < 0) {
		wpa_printf(MSG_ERROR, "Driver interface rejected param");
	}
}