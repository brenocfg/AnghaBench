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
struct hostapd_data {struct hostapd_bss_config* conf; } ;
struct hostapd_bss_config {char* bridge; int /*<<< orphan*/  isolate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_BR_MULTICAST_SNOOPING ; 
 int /*<<< orphan*/  DRV_BR_NET_PARAM_GARP_ACCEPT ; 
 int /*<<< orphan*/  DRV_BR_PORT_ATTR_HAIRPIN_MODE ; 
 int /*<<< orphan*/  DRV_BR_PORT_ATTR_PROXYARP ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ hostapd_drv_br_port_set_attr (struct hostapd_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ hostapd_drv_br_set_net_param (struct hostapd_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int x_snoop_init(struct hostapd_data *hapd)
{
	struct hostapd_bss_config *conf = hapd->conf;

	if (!conf->isolate) {
		wpa_printf(MSG_DEBUG,
			   "x_snoop: ap_isolate must be enabled for x_snoop");
		return -1;
	}

	if (conf->bridge[0] == '\0') {
		wpa_printf(MSG_DEBUG,
			   "x_snoop: Bridge must be configured for x_snoop");
		return -1;
	}

	if (hostapd_drv_br_port_set_attr(hapd, DRV_BR_PORT_ATTR_HAIRPIN_MODE,
					 1)) {
		wpa_printf(MSG_DEBUG,
			   "x_snoop: Failed to enable hairpin_mode on the bridge port");
		return -1;
	}

	if (hostapd_drv_br_port_set_attr(hapd, DRV_BR_PORT_ATTR_PROXYARP, 1)) {
		wpa_printf(MSG_DEBUG,
			   "x_snoop: Failed to enable proxyarp on the bridge port");
		return -1;
	}

	if (hostapd_drv_br_set_net_param(hapd, DRV_BR_NET_PARAM_GARP_ACCEPT,
					 1)) {
		wpa_printf(MSG_DEBUG,
			   "x_snoop: Failed to enable accepting gratuitous ARP on the bridge");
		return -1;
	}

#ifdef CONFIG_IPV6
	if (hostapd_drv_br_set_net_param(hapd, DRV_BR_MULTICAST_SNOOPING, 1)) {
		wpa_printf(MSG_DEBUG,
			   "x_snoop: Failed to enable multicast snooping on the bridge");
		return -1;
	}
#endif /* CONFIG_IPV6 */

	return 0;
}