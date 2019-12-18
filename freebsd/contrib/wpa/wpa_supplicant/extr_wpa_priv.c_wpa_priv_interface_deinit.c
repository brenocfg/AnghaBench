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
struct wpa_priv_interface {scalar_t__ fd; struct wpa_priv_interface* sock_name; struct wpa_priv_interface* driver_name; struct wpa_priv_interface* ifname; scalar_t__* l2; scalar_t__ drv_global_priv; TYPE_1__* driver; scalar_t__ drv_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* global_deinit ) (scalar_t__) ;int /*<<< orphan*/  (* deinit ) (scalar_t__) ;} ;

/* Variables and functions */
 int WPA_PRIV_MAX_L2 ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  eloop_unregister_read_sock (scalar_t__) ; 
 int /*<<< orphan*/  l2_packet_deinit (scalar_t__) ; 
 int /*<<< orphan*/  os_free (struct wpa_priv_interface*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 int /*<<< orphan*/  unlink (struct wpa_priv_interface*) ; 

__attribute__((used)) static void wpa_priv_interface_deinit(struct wpa_priv_interface *iface)
{
	int i;

	if (iface->drv_priv) {
		if (iface->driver->deinit)
			iface->driver->deinit(iface->drv_priv);
		if (iface->drv_global_priv)
			iface->driver->global_deinit(iface->drv_global_priv);
	}

	if (iface->fd >= 0) {
		eloop_unregister_read_sock(iface->fd);
		close(iface->fd);
		unlink(iface->sock_name);
	}

	for (i = 0; i < WPA_PRIV_MAX_L2; i++) {
		if (iface->l2[i])
			l2_packet_deinit(iface->l2[i]);
	}

	os_free(iface->ifname);
	os_free(iface->driver_name);
	os_free(iface->sock_name);
	os_free(iface);
}