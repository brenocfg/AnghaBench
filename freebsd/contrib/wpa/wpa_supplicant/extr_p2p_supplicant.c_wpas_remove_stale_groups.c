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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int /*<<< orphan*/  conf; } ;
struct wpa_ssid {size_t ssid_len; scalar_t__ mode; int num_p2p_clients; int /*<<< orphan*/  const* p2p_client_list; int /*<<< orphan*/  id; int /*<<< orphan*/  const* ssid; int /*<<< orphan*/  const* bssid; } ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ WPAS_MODE_P2P_GO ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_memmove (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  p2p_config_write (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_config_remove_network (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_notify_persistent_group_removed (struct wpa_supplicant*,struct wpa_ssid*) ; 
 struct wpa_ssid* wpas_p2p_get_persistent (struct wpa_supplicant*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpas_remove_stale_groups(void *ctx, const u8 *peer, const u8 *go,
				    const u8 *ssid, size_t ssid_len)
{
	struct wpa_supplicant *wpa_s = ctx;
	struct wpa_ssid *s;
	int save_config = 0;
	size_t i;

	/* Start with our first choice of Persistent Groups */
	while ((s = wpas_p2p_get_persistent(wpa_s, peer, NULL, 0))) {
		if (go && ssid && ssid_len &&
		    s->ssid_len == ssid_len &&
		    os_memcmp(go, s->bssid, ETH_ALEN) == 0 &&
		    os_memcmp(ssid, s->ssid, ssid_len) == 0)
			break;

		/* Remove stale persistent group */
		if (s->mode != WPAS_MODE_P2P_GO || s->num_p2p_clients <= 1) {
			wpa_dbg(wpa_s, MSG_DEBUG,
				"P2P: Remove stale persistent group id=%d",
				s->id);
			wpas_notify_persistent_group_removed(wpa_s, s);
			wpa_config_remove_network(wpa_s->conf, s->id);
			save_config = 1;
			continue;
		}

		for (i = 0; i < s->num_p2p_clients; i++) {
			if (os_memcmp(s->p2p_client_list + i * 2 * ETH_ALEN,
				      peer, ETH_ALEN) != 0)
				continue;

			os_memmove(s->p2p_client_list + i * 2 * ETH_ALEN,
				   s->p2p_client_list + (i + 1) * 2 * ETH_ALEN,
				   (s->num_p2p_clients - i - 1) * 2 * ETH_ALEN);
			break;
		}
		s->num_p2p_clients--;
		save_config = 1;
	}

	if (save_config)
		p2p_config_write(wpa_s);

	/* Return TRUE if valid SSID remains */
	return s != NULL;
}