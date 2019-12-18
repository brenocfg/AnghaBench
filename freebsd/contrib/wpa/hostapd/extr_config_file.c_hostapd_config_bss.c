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
struct hostapd_config {struct hostapd_bss_config* last_bss; scalar_t__ num_bss; struct hostapd_bss_config** bss; } ;
struct TYPE_2__ {int /*<<< orphan*/  vlan; } ;
struct hostapd_bss_config {int /*<<< orphan*/  iface; TYPE_1__ ssid; int /*<<< orphan*/ * radius; } ;

/* Variables and functions */
 scalar_t__ IFNAMSIZ ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  hostapd_config_defaults_bss (struct hostapd_bss_config*) ; 
 int /*<<< orphan*/  os_free (struct hostapd_bss_config*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct hostapd_bss_config** os_realloc_array (struct hostapd_bss_config**,scalar_t__,int) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 void* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hostapd_config_bss(struct hostapd_config *conf, const char *ifname)
{
	struct hostapd_bss_config **all, *bss;

	if (*ifname == '\0')
		return -1;

	all = os_realloc_array(conf->bss, conf->num_bss + 1,
			       sizeof(struct hostapd_bss_config *));
	if (all == NULL) {
		wpa_printf(MSG_ERROR, "Failed to allocate memory for "
			   "multi-BSS entry");
		return -1;
	}
	conf->bss = all;

	bss = os_zalloc(sizeof(*bss));
	if (bss == NULL)
		return -1;
	bss->radius = os_zalloc(sizeof(*bss->radius));
	if (bss->radius == NULL) {
		wpa_printf(MSG_ERROR, "Failed to allocate memory for "
			   "multi-BSS RADIUS data");
		os_free(bss);
		return -1;
	}

	conf->bss[conf->num_bss++] = bss;
	conf->last_bss = bss;

	hostapd_config_defaults_bss(bss);
	os_strlcpy(bss->iface, ifname, sizeof(bss->iface));
	os_memcpy(bss->ssid.vlan, bss->iface, IFNAMSIZ + 1);

	return 0;
}