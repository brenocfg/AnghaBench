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
struct wpa_supplicant {int /*<<< orphan*/  own_addr; int /*<<< orphan*/  pending_interface_addr; } ;
struct wpa_ssid {size_t ssid_len; scalar_t__ mode; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 scalar_t__ WPAS_MODE_P2P_GO ; 
 int /*<<< orphan*/  WPA_IF_P2P_GO ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ wpas_p2p_add_group_interface (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpas_p2p_create_iface (struct wpa_supplicant*) ; 
 struct wpa_ssid* wpas_p2p_get_persistent (struct wpa_supplicant*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int wpas_get_persistent_group(void *ctx, const u8 *addr, const u8 *ssid,
				     size_t ssid_len, u8 *go_dev_addr,
				     u8 *ret_ssid, size_t *ret_ssid_len,
				     u8 *intended_iface_addr)
{
	struct wpa_supplicant *wpa_s = ctx;
	struct wpa_ssid *s;

	s = wpas_p2p_get_persistent(wpa_s, addr, ssid, ssid_len);
	if (s) {
		os_memcpy(ret_ssid, s->ssid, s->ssid_len);
		*ret_ssid_len = s->ssid_len;
		os_memcpy(go_dev_addr, s->bssid, ETH_ALEN);

		if (s->mode != WPAS_MODE_P2P_GO) {
			os_memset(intended_iface_addr, 0, ETH_ALEN);
		} else if (wpas_p2p_create_iface(wpa_s)) {
			if (wpas_p2p_add_group_interface(wpa_s, WPA_IF_P2P_GO))
				return 0;

			os_memcpy(intended_iface_addr,
				  wpa_s->pending_interface_addr, ETH_ALEN);
		} else {
			os_memcpy(intended_iface_addr, wpa_s->own_addr,
				  ETH_ALEN);
		}
		return 1;
	}

	return 0;
}