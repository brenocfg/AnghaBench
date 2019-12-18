#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct atheros_driver_data {scalar_t__ ioctl_sock; int /*<<< orphan*/ * sock_raw; int /*<<< orphan*/ * sock_xmit; int /*<<< orphan*/ * sock_recv; int /*<<< orphan*/  iface; int /*<<< orphan*/  netlink; scalar_t__ wps_probe_resp_ie; scalar_t__ wps_beacon_ie; scalar_t__ wpa_ie; } ;

/* Variables and functions */
 int /*<<< orphan*/  atheros_reset_appfilter (struct atheros_driver_data*) ; 
 int /*<<< orphan*/  atheros_set_opt_ie (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  l2_packet_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linux_set_iface_flags (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct atheros_driver_data*) ; 
 int /*<<< orphan*/  wpabuf_free (scalar_t__) ; 

__attribute__((used)) static void
atheros_deinit(void *priv)
{
	struct atheros_driver_data *drv = priv;

	atheros_reset_appfilter(drv);

	if (drv->wpa_ie || drv->wps_beacon_ie || drv->wps_probe_resp_ie) {
		atheros_set_opt_ie(priv, NULL, 0);
		wpabuf_free(drv->wpa_ie);
		wpabuf_free(drv->wps_beacon_ie);
		wpabuf_free(drv->wps_probe_resp_ie);
	}
	netlink_deinit(drv->netlink);
	(void) linux_set_iface_flags(drv->ioctl_sock, drv->iface, 0);
	if (drv->ioctl_sock >= 0)
		close(drv->ioctl_sock);
	if (drv->sock_recv != NULL && drv->sock_recv != drv->sock_xmit)
		l2_packet_deinit(drv->sock_recv);
	if (drv->sock_xmit != NULL)
		l2_packet_deinit(drv->sock_xmit);
	if (drv->sock_raw)
		l2_packet_deinit(drv->sock_raw);
	os_free(drv);
}