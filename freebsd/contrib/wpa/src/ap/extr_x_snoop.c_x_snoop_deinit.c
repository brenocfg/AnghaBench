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
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_BR_NET_PARAM_GARP_ACCEPT ; 
 int /*<<< orphan*/  DRV_BR_PORT_ATTR_HAIRPIN_MODE ; 
 int /*<<< orphan*/  DRV_BR_PORT_ATTR_PROXYARP ; 
 int /*<<< orphan*/  hostapd_drv_br_port_set_attr (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_drv_br_set_net_param (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void x_snoop_deinit(struct hostapd_data *hapd)
{
	hostapd_drv_br_set_net_param(hapd, DRV_BR_NET_PARAM_GARP_ACCEPT, 0);
	hostapd_drv_br_port_set_attr(hapd, DRV_BR_PORT_ATTR_PROXYARP, 0);
	hostapd_drv_br_port_set_attr(hapd, DRV_BR_PORT_ATTR_HAIRPIN_MODE, 0);
}