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
struct hostapd_iface {size_t num_bss; struct hostapd_data** bss; struct hostapd_config* conf; struct hapd_interfaces* interfaces; int /*<<< orphan*/ * config_fname; } ;
struct hostapd_data {TYPE_1__* conf; struct hostapd_config* iconf; } ;
struct hostapd_config {TYPE_1__** bss; int /*<<< orphan*/  vht_capab; int /*<<< orphan*/  ht_capab; int /*<<< orphan*/  ieee80211ac; int /*<<< orphan*/  ieee80211n; int /*<<< orphan*/  secondary_channel; int /*<<< orphan*/  acs; int /*<<< orphan*/  channel; } ;
struct hapd_interfaces {size_t count; struct hostapd_iface** iface; struct hostapd_config* (* config_read_cb ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  hostapd_clear_old (struct hostapd_iface*) ; 
 int /*<<< orphan*/  hostapd_config_free (struct hostapd_config*) ; 
 int hostapd_enable_iface (struct hostapd_iface*) ; 
 int /*<<< orphan*/  hostapd_get_oper_centr_freq_seg0_idx (struct hostapd_config*) ; 
 int /*<<< orphan*/  hostapd_get_oper_centr_freq_seg1_idx (struct hostapd_config*) ; 
 int /*<<< orphan*/  hostapd_get_oper_chwidth (struct hostapd_config*) ; 
 scalar_t__ hostapd_iface_conf_changed (struct hostapd_config*,struct hostapd_config*) ; 
 struct hostapd_iface* hostapd_init (struct hapd_interfaces*,char*) ; 
 int /*<<< orphan*/  hostapd_reload_bss (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_remove_iface (struct hapd_interfaces*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_set_oper_centr_freq_seg0_idx (struct hostapd_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_set_oper_centr_freq_seg1_idx (struct hostapd_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_set_oper_chwidth (struct hostapd_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_strdup (int /*<<< orphan*/ *) ; 
 struct hostapd_config* stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int hostapd_reload_config(struct hostapd_iface *iface)
{
	struct hapd_interfaces *interfaces = iface->interfaces;
	struct hostapd_data *hapd = iface->bss[0];
	struct hostapd_config *newconf, *oldconf;
	size_t j;

	if (iface->config_fname == NULL) {
		/* Only in-memory config in use - assume it has been updated */
		hostapd_clear_old(iface);
		for (j = 0; j < iface->num_bss; j++)
			hostapd_reload_bss(iface->bss[j]);
		return 0;
	}

	if (iface->interfaces == NULL ||
	    iface->interfaces->config_read_cb == NULL)
		return -1;
	newconf = iface->interfaces->config_read_cb(iface->config_fname);
	if (newconf == NULL)
		return -1;

	hostapd_clear_old(iface);

	oldconf = hapd->iconf;
	if (hostapd_iface_conf_changed(newconf, oldconf)) {
		char *fname;
		int res;

		wpa_printf(MSG_DEBUG,
			   "Configuration changes include interface/BSS modification - force full disable+enable sequence");
		fname = os_strdup(iface->config_fname);
		if (!fname) {
			hostapd_config_free(newconf);
			return -1;
		}
		hostapd_remove_iface(interfaces, hapd->conf->iface);
		iface = hostapd_init(interfaces, fname);
		os_free(fname);
		hostapd_config_free(newconf);
		if (!iface) {
			wpa_printf(MSG_ERROR,
				   "Failed to initialize interface on config reload");
			return -1;
		}
		iface->interfaces = interfaces;
		interfaces->iface[interfaces->count] = iface;
		interfaces->count++;
		res = hostapd_enable_iface(iface);
		if (res < 0)
			wpa_printf(MSG_ERROR,
				   "Failed to enable interface on config reload");
		return res;
	}
	iface->conf = newconf;

	for (j = 0; j < iface->num_bss; j++) {
		hapd = iface->bss[j];
		hapd->iconf = newconf;
		hapd->iconf->channel = oldconf->channel;
		hapd->iconf->acs = oldconf->acs;
		hapd->iconf->secondary_channel = oldconf->secondary_channel;
		hapd->iconf->ieee80211n = oldconf->ieee80211n;
		hapd->iconf->ieee80211ac = oldconf->ieee80211ac;
		hapd->iconf->ht_capab = oldconf->ht_capab;
		hapd->iconf->vht_capab = oldconf->vht_capab;
		hostapd_set_oper_chwidth(hapd->iconf,
					 hostapd_get_oper_chwidth(oldconf));
		hostapd_set_oper_centr_freq_seg0_idx(
			hapd->iconf,
			hostapd_get_oper_centr_freq_seg0_idx(oldconf));
		hostapd_set_oper_centr_freq_seg1_idx(
			hapd->iconf,
			hostapd_get_oper_centr_freq_seg1_idx(oldconf));
		hapd->conf = newconf->bss[j];
		hostapd_reload_bss(hapd);
	}

	hostapd_config_free(oldconf);


	return 0;
}