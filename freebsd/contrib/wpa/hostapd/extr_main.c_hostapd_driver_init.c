#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct wpa_init_params {int* bssid; size_t num_bridge; scalar_t__** bridge; int /*<<< orphan*/  own_addr; int /*<<< orphan*/  use_pae_group_addr; int /*<<< orphan*/  driver_params; int /*<<< orphan*/  ifname; int /*<<< orphan*/ * global_priv; } ;
struct wpa_driver_capa {int /*<<< orphan*/  max_acl_mac_addrs; int /*<<< orphan*/  extended_capa_len; int /*<<< orphan*/  extended_capa_mask; int /*<<< orphan*/  extended_capa; int /*<<< orphan*/  probe_resp_offloads; int /*<<< orphan*/  smps_modes; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__* wowlan_triggers ;
struct hostapd_iface {int /*<<< orphan*/  drv_max_acl_mac_addrs; int /*<<< orphan*/  extended_capa_len; int /*<<< orphan*/  extended_capa_mask; int /*<<< orphan*/  extended_capa; int /*<<< orphan*/  probe_resp_offloads; int /*<<< orphan*/  smps_modes; int /*<<< orphan*/  drv_flags; int /*<<< orphan*/  interfaces; struct hostapd_data** bss; } ;
struct hostapd_data {int /*<<< orphan*/ * drv_priv; TYPE_3__* driver; int /*<<< orphan*/  own_addr; struct hostapd_bss_config* conf; TYPE_2__* iface; TYPE_1__* iconf; } ;
struct hostapd_bss_config {int* bssid; int /*<<< orphan*/  wowlan_triggers; scalar_t__* bridge; int /*<<< orphan*/  use_pae_group_addr; int /*<<< orphan*/  iface; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_8__ {int /*<<< orphan*/ ** drv_priv; } ;
struct TYPE_7__ {scalar_t__ (* get_capa ) (int /*<<< orphan*/ *,struct wpa_driver_capa*) ;scalar_t__ (* set_wowlan ) (int /*<<< orphan*/ *,scalar_t__**) ;int /*<<< orphan*/  name; int /*<<< orphan*/ * (* hapd_init ) (struct hostapd_data*,struct wpa_init_params*) ;int /*<<< orphan*/ * (* global_init ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {size_t num_bss; struct hostapd_data** bss; } ;
struct TYPE_5__ {int /*<<< orphan*/  driver_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 TYPE_4__ global ; 
 int /*<<< orphan*/  hostapd_get_ext_capa (struct hostapd_iface*) ; 
 scalar_t__** os_calloc (size_t,int) ; 
 int /*<<< orphan*/  os_free (scalar_t__**) ; 
 int /*<<< orphan*/  os_memset (struct wpa_init_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (struct hostapd_data*,struct wpa_init_params*) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ *,struct wpa_driver_capa*) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ *,scalar_t__**) ; 
 TYPE_3__** wpa_drivers ; 
 scalar_t__** wpa_get_wowlan_triggers (int /*<<< orphan*/ ,struct wpa_driver_capa*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int hostapd_driver_init(struct hostapd_iface *iface)
{
	struct wpa_init_params params;
	size_t i;
	struct hostapd_data *hapd = iface->bss[0];
	struct hostapd_bss_config *conf = hapd->conf;
	u8 *b = conf->bssid;
	struct wpa_driver_capa capa;

	if (hapd->driver == NULL || hapd->driver->hapd_init == NULL) {
		wpa_printf(MSG_ERROR, "No hostapd driver wrapper available");
		return -1;
	}

	/* Initialize the driver interface */
	if (!(b[0] | b[1] | b[2] | b[3] | b[4] | b[5]))
		b = NULL;

	os_memset(&params, 0, sizeof(params));
	for (i = 0; wpa_drivers[i]; i++) {
		if (wpa_drivers[i] != hapd->driver)
			continue;

		if (global.drv_priv[i] == NULL &&
		    wpa_drivers[i]->global_init) {
			global.drv_priv[i] =
				wpa_drivers[i]->global_init(iface->interfaces);
			if (global.drv_priv[i] == NULL) {
				wpa_printf(MSG_ERROR, "Failed to initialize "
					   "driver '%s'",
					   wpa_drivers[i]->name);
				return -1;
			}
		}

		params.global_priv = global.drv_priv[i];
		break;
	}
	params.bssid = b;
	params.ifname = hapd->conf->iface;
	params.driver_params = hapd->iconf->driver_params;
	params.use_pae_group_addr = hapd->conf->use_pae_group_addr;

	params.num_bridge = hapd->iface->num_bss;
	params.bridge = os_calloc(hapd->iface->num_bss, sizeof(char *));
	if (params.bridge == NULL)
		return -1;
	for (i = 0; i < hapd->iface->num_bss; i++) {
		struct hostapd_data *bss = hapd->iface->bss[i];
		if (bss->conf->bridge[0])
			params.bridge[i] = bss->conf->bridge;
	}

	params.own_addr = hapd->own_addr;

	hapd->drv_priv = hapd->driver->hapd_init(hapd, &params);
	os_free(params.bridge);
	if (hapd->drv_priv == NULL) {
		wpa_printf(MSG_ERROR, "%s driver initialization failed.",
			   hapd->driver->name);
		hapd->driver = NULL;
		return -1;
	}

	if (hapd->driver->get_capa &&
	    hapd->driver->get_capa(hapd->drv_priv, &capa) == 0) {
		struct wowlan_triggers *triggs;

		iface->drv_flags = capa.flags;
		iface->smps_modes = capa.smps_modes;
		iface->probe_resp_offloads = capa.probe_resp_offloads;
		/*
		 * Use default extended capa values from per-radio information
		 */
		iface->extended_capa = capa.extended_capa;
		iface->extended_capa_mask = capa.extended_capa_mask;
		iface->extended_capa_len = capa.extended_capa_len;
		iface->drv_max_acl_mac_addrs = capa.max_acl_mac_addrs;

		/*
		 * Override extended capa with per-interface type (AP), if
		 * available from the driver.
		 */
		hostapd_get_ext_capa(iface);

		triggs = wpa_get_wowlan_triggers(conf->wowlan_triggers, &capa);
		if (triggs && hapd->driver->set_wowlan) {
			if (hapd->driver->set_wowlan(hapd->drv_priv, triggs))
				wpa_printf(MSG_ERROR, "set_wowlan failed");
		}
		os_free(triggs);
	}

	return 0;
}