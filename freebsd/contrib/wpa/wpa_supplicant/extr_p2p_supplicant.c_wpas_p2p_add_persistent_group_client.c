#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const u8 ;
struct wpa_supplicant {TYPE_2__* conf; int /*<<< orphan*/  confname; struct wpa_ssid* current_ssid; TYPE_1__* global; } ;
struct wpa_ssid {scalar_t__ mode; int disabled; scalar_t__ ssid_len; size_t num_p2p_clients; int /*<<< orphan*/  const* p2p_client_list; int /*<<< orphan*/  const* ssid; struct wpa_ssid* next; int /*<<< orphan*/  p2p_persistent_group; } ;
struct TYPE_4__ {scalar_t__ update_config; struct wpa_ssid* ssid; } ;
struct TYPE_3__ {struct wpa_supplicant* p2p_init_wpa_s; } ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int P2P_MAX_STORED_CLIENTS ; 
 scalar_t__ WPAS_MODE_P2P_GO ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_memmove (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/  const*,int,size_t) ; 
 int /*<<< orphan*/  const* os_realloc_array (int /*<<< orphan*/  const*,int,int) ; 
 scalar_t__ wpa_config_write (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wpas_p2p_add_persistent_group_client(struct wpa_supplicant *wpa_s,
						 const u8 *addr)
{
	struct wpa_ssid *ssid, *s;
	u8 *n;
	size_t i;
	int found = 0;
	struct wpa_supplicant *p2p_wpa_s = wpa_s->global->p2p_init_wpa_s;

	ssid = wpa_s->current_ssid;
	if (ssid == NULL || ssid->mode != WPAS_MODE_P2P_GO ||
	    !ssid->p2p_persistent_group)
		return;

	for (s = p2p_wpa_s->conf->ssid; s; s = s->next) {
		if (s->disabled != 2 || s->mode != WPAS_MODE_P2P_GO)
			continue;

		if (s->ssid_len == ssid->ssid_len &&
		    os_memcmp(s->ssid, ssid->ssid, s->ssid_len) == 0)
			break;
	}

	if (s == NULL)
		return;

	for (i = 0; s->p2p_client_list && i < s->num_p2p_clients; i++) {
		if (os_memcmp(s->p2p_client_list + i * 2 * ETH_ALEN, addr,
			      ETH_ALEN) != 0)
			continue;

		if (i == s->num_p2p_clients - 1)
			return; /* already the most recent entry */

		/* move the entry to mark it most recent */
		os_memmove(s->p2p_client_list + i * 2 * ETH_ALEN,
			   s->p2p_client_list + (i + 1) * 2 * ETH_ALEN,
			   (s->num_p2p_clients - i - 1) * 2 * ETH_ALEN);
		os_memcpy(s->p2p_client_list +
			  (s->num_p2p_clients - 1) * 2 * ETH_ALEN, addr,
			  ETH_ALEN);
		os_memset(s->p2p_client_list +
			  (s->num_p2p_clients - 1) * 2 * ETH_ALEN + ETH_ALEN,
			  0xff, ETH_ALEN);
		found = 1;
		break;
	}

	if (!found && s->num_p2p_clients < P2P_MAX_STORED_CLIENTS) {
		n = os_realloc_array(s->p2p_client_list,
				     s->num_p2p_clients + 1, 2 * ETH_ALEN);
		if (n == NULL)
			return;
		os_memcpy(n + s->num_p2p_clients * 2 * ETH_ALEN, addr,
			  ETH_ALEN);
		os_memset(n + s->num_p2p_clients * 2 * ETH_ALEN + ETH_ALEN,
			  0xff, ETH_ALEN);
		s->p2p_client_list = n;
		s->num_p2p_clients++;
	} else if (!found && s->p2p_client_list) {
		/* Not enough room for an additional entry - drop the oldest
		 * entry */
		os_memmove(s->p2p_client_list,
			   s->p2p_client_list + 2 * ETH_ALEN,
			   (s->num_p2p_clients - 1) * 2 * ETH_ALEN);
		os_memcpy(s->p2p_client_list +
			  (s->num_p2p_clients - 1) * 2 * ETH_ALEN,
			  addr, ETH_ALEN);
		os_memset(s->p2p_client_list +
			  (s->num_p2p_clients - 1) * 2 * ETH_ALEN + ETH_ALEN,
			  0xff, ETH_ALEN);
	}

	if (p2p_wpa_s->conf->update_config &&
	    wpa_config_write(p2p_wpa_s->confname, p2p_wpa_s->conf))
		wpa_printf(MSG_DEBUG, "P2P: Failed to update configuration");
}