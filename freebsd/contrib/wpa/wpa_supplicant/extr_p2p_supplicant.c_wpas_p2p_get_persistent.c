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
struct wpa_supplicant {TYPE_1__* conf; } ;
struct wpa_ssid {int disabled; size_t ssid_len; scalar_t__ mode; size_t num_p2p_clients; int /*<<< orphan*/  const* p2p_client_list; int /*<<< orphan*/  const* bssid; int /*<<< orphan*/  const* ssid; struct wpa_ssid* next; } ;
struct TYPE_2__ {struct wpa_ssid* ssid; } ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 scalar_t__ WPAS_MODE_P2P_GO ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

struct wpa_ssid * wpas_p2p_get_persistent(struct wpa_supplicant *wpa_s,
					  const u8 *addr, const u8 *ssid,
					  size_t ssid_len)
{
	struct wpa_ssid *s;
	size_t i;

	for (s = wpa_s->conf->ssid; s; s = s->next) {
		if (s->disabled != 2)
			continue;
		if (ssid &&
		    (ssid_len != s->ssid_len ||
		     os_memcmp(ssid, s->ssid, ssid_len) != 0))
			continue;
		if (addr == NULL) {
			if (s->mode == WPAS_MODE_P2P_GO)
				return s;
			continue;
		}
		if (os_memcmp(s->bssid, addr, ETH_ALEN) == 0)
			return s; /* peer is GO in the persistent group */
		if (s->mode != WPAS_MODE_P2P_GO || s->p2p_client_list == NULL)
			continue;
		for (i = 0; i < s->num_p2p_clients; i++) {
			if (os_memcmp(s->p2p_client_list + i * 2 * ETH_ALEN,
				      addr, ETH_ALEN) == 0)
				return s; /* peer is P2P client in persistent
					   * group */
		}
	}

	return NULL;
}