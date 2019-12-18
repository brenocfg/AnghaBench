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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int /*<<< orphan*/  go_dev_addr; struct wpa_ssid* current_ssid; struct wpa_supplicant* next; TYPE_1__* global; } ;
struct wpa_ssid {scalar_t__ mode; int /*<<< orphan*/  p2p_group; } ;
struct TYPE_2__ {struct wpa_supplicant* ifaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ WPAS_MODE_INFRA ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

struct wpa_supplicant * wpas_get_p2p_client_iface(struct wpa_supplicant *wpa_s,
						  const u8 *peer_dev_addr)
{
	for (wpa_s = wpa_s->global->ifaces; wpa_s; wpa_s = wpa_s->next) {
		struct wpa_ssid *ssid = wpa_s->current_ssid;
		if (ssid && (ssid->mode != WPAS_MODE_INFRA || !ssid->p2p_group))
			continue;
		if (os_memcmp(wpa_s->go_dev_addr, peer_dev_addr, ETH_ALEN) == 0)
			return wpa_s;
	}

	return NULL;
}