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
struct wpa_supplicant {scalar_t__ max_stations; struct p2p_group* p2p_group; TYPE_4__* global; TYPE_3__* p2pdev; TYPE_1__* conf; int /*<<< orphan*/  own_addr; } ;
struct wpa_ssid {scalar_t__ mode; int /*<<< orphan*/  frequency; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; scalar_t__ p2p_persistent_group; int /*<<< orphan*/  p2p_group; } ;
struct p2p_group_config {int persistent_group; scalar_t__ max_clients; int ip_addr_alloc; int /*<<< orphan*/  idle_update; int /*<<< orphan*/  ie_update; struct wpa_supplicant* cb_ctx; int /*<<< orphan*/  freq; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  interface_addr; } ;
struct p2p_group {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * p2p; scalar_t__ p2p_disabled; } ;
struct TYPE_7__ {TYPE_2__* conf; } ;
struct TYPE_6__ {int /*<<< orphan*/  ip_addr_start; } ;
struct TYPE_5__ {scalar_t__ max_num_sta; scalar_t__ persistent_reconnect; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ WPAS_MODE_P2P_GROUP_FORMATION ; 
 scalar_t__ WPA_GET_BE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct p2p_group_config*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct p2p_group_config* os_zalloc (int) ; 
 struct p2p_group* p2p_group_init (int /*<<< orphan*/ *,struct p2p_group_config*) ; 
 int /*<<< orphan*/  p2p_group_notif_formation_done (struct p2p_group*) ; 
 int /*<<< orphan*/  wpas_p2p_idle_update ; 
 int /*<<< orphan*/  wpas_p2p_ie_update ; 

struct p2p_group * wpas_p2p_group_init(struct wpa_supplicant *wpa_s,
				       struct wpa_ssid *ssid)
{
	struct p2p_group *group;
	struct p2p_group_config *cfg;

	if (wpa_s->global->p2p_disabled || wpa_s->global->p2p == NULL ||
	    !ssid->p2p_group)
		return NULL;

	cfg = os_zalloc(sizeof(*cfg));
	if (cfg == NULL)
		return NULL;

	if (ssid->p2p_persistent_group && wpa_s->conf->persistent_reconnect)
		cfg->persistent_group = 2;
	else if (ssid->p2p_persistent_group)
		cfg->persistent_group = 1;
	os_memcpy(cfg->interface_addr, wpa_s->own_addr, ETH_ALEN);
	if (wpa_s->max_stations &&
	    wpa_s->max_stations < wpa_s->conf->max_num_sta)
		cfg->max_clients = wpa_s->max_stations;
	else
		cfg->max_clients = wpa_s->conf->max_num_sta;
	os_memcpy(cfg->ssid, ssid->ssid, ssid->ssid_len);
	cfg->ssid_len = ssid->ssid_len;
	cfg->freq = ssid->frequency;
	cfg->cb_ctx = wpa_s;
	cfg->ie_update = wpas_p2p_ie_update;
	cfg->idle_update = wpas_p2p_idle_update;
	cfg->ip_addr_alloc = WPA_GET_BE32(wpa_s->p2pdev->conf->ip_addr_start)
		!= 0;

	group = p2p_group_init(wpa_s->global->p2p, cfg);
	if (group == NULL)
		os_free(cfg);
	if (ssid->mode != WPAS_MODE_P2P_GROUP_FORMATION)
		p2p_group_notif_formation_done(group);
	wpa_s->p2p_group = group;
	return group;
}