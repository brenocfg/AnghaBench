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
struct hostapd_iface {int dummy; } ;
struct hostapd_data {int ctrl_sock; int dhcp_sock; int /*<<< orphan*/  sae_commit_queue; int /*<<< orphan*/  l2_oui_queue; int /*<<< orphan*/  l2_queue; int /*<<< orphan*/  nr_db; int /*<<< orphan*/  ctrl_dst; int /*<<< orphan*/  driver; struct hostapd_iface* iface; struct hostapd_bss_config* conf; struct hostapd_config* iconf; int /*<<< orphan*/  new_assoc_sta_cb; } ;
struct hostapd_config {int /*<<< orphan*/  driver; } ;
struct hostapd_bss_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_new_assoc_sta ; 
 struct hostapd_data* os_zalloc (int) ; 

struct hostapd_data *
hostapd_alloc_bss_data(struct hostapd_iface *hapd_iface,
		       struct hostapd_config *conf,
		       struct hostapd_bss_config *bss)
{
	struct hostapd_data *hapd;

	hapd = os_zalloc(sizeof(*hapd));
	if (hapd == NULL)
		return NULL;

	hapd->new_assoc_sta_cb = hostapd_new_assoc_sta;
	hapd->iconf = conf;
	hapd->conf = bss;
	hapd->iface = hapd_iface;
	if (conf)
		hapd->driver = conf->driver;
	hapd->ctrl_sock = -1;
	dl_list_init(&hapd->ctrl_dst);
	dl_list_init(&hapd->nr_db);
	hapd->dhcp_sock = -1;
#ifdef CONFIG_IEEE80211R_AP
	dl_list_init(&hapd->l2_queue);
	dl_list_init(&hapd->l2_oui_queue);
#endif /* CONFIG_IEEE80211R_AP */
#ifdef CONFIG_SAE
	dl_list_init(&hapd->sae_commit_queue);
#endif /* CONFIG_SAE */

	return hapd;
}