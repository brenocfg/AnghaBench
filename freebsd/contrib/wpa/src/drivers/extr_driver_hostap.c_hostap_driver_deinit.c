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
struct hostap_driver_data {scalar_t__ ioctl_sock; scalar_t__ sock; int /*<<< orphan*/  wps_ie; int /*<<< orphan*/  generic_ie; int /*<<< orphan*/  netlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRISM2_PARAM_HOSTAPD ; 
 int /*<<< orphan*/  PRISM2_PARAM_HOSTAPD_STA ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (struct hostap_driver_data*) ; 
 int /*<<< orphan*/  hostap_ioctl_prism2param (struct hostap_driver_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostap_set_iface_flags (struct hostap_driver_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostap_driver_deinit(void *priv)
{
	struct hostap_driver_data *drv = priv;

	netlink_deinit(drv->netlink);
	(void) hostap_set_iface_flags(drv, 0);
	(void) hostap_ioctl_prism2param(drv, PRISM2_PARAM_HOSTAPD, 0);
	(void) hostap_ioctl_prism2param(drv, PRISM2_PARAM_HOSTAPD_STA, 0);

	if (drv->ioctl_sock >= 0)
		close(drv->ioctl_sock);

	if (drv->sock >= 0)
		close(drv->sock);

	os_free(drv->generic_ie);
	os_free(drv->wps_ie);

	free(drv);
}