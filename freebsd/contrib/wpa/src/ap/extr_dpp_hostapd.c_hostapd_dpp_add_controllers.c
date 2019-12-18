#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hostapd_data {TYPE_3__* iface; TYPE_1__* conf; } ;
struct dpp_relay_config {int /*<<< orphan*/  pkhash; int /*<<< orphan*/ * ipaddr; int /*<<< orphan*/  gas_resp_tx; int /*<<< orphan*/  tx; struct hostapd_data* cb_ctx; } ;
struct dpp_controller_conf {int /*<<< orphan*/  pkhash; int /*<<< orphan*/  ipaddr; struct dpp_controller_conf* next; } ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_6__ {TYPE_2__* interfaces; } ;
struct TYPE_5__ {int /*<<< orphan*/  dpp; } ;
struct TYPE_4__ {struct dpp_controller_conf* dpp_controller; } ;

/* Variables and functions */
 scalar_t__ dpp_relay_add_controller (int /*<<< orphan*/ ,struct dpp_relay_config*) ; 
 int /*<<< orphan*/  hostapd_dpp_relay_gas_resp_tx ; 
 int /*<<< orphan*/  hostapd_dpp_relay_tx ; 
 int /*<<< orphan*/  os_memset (struct dpp_relay_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hostapd_dpp_add_controllers(struct hostapd_data *hapd)
{
#ifdef CONFIG_DPP2
	struct dpp_controller_conf *ctrl;
	struct dpp_relay_config config;

	os_memset(&config, 0, sizeof(config));
	config.cb_ctx = hapd;
	config.tx = hostapd_dpp_relay_tx;
	config.gas_resp_tx = hostapd_dpp_relay_gas_resp_tx;
	for (ctrl = hapd->conf->dpp_controller; ctrl; ctrl = ctrl->next) {
		config.ipaddr = &ctrl->ipaddr;
		config.pkhash = ctrl->pkhash;
		if (dpp_relay_add_controller(hapd->iface->interfaces->dpp,
					     &config) < 0)
			return -1;
	}
#endif /* CONFIG_DPP2 */

	return 0;
}