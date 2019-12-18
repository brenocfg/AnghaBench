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
struct wpa_tdls_peer {int /*<<< orphan*/ * ht_capabilities; } ;
struct wpa_eapol_ie_parse {int /*<<< orphan*/  ht_capabilities; } ;
struct ieee80211_ht_capabilities {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int copy_peer_ht_capab(const struct wpa_eapol_ie_parse *kde,
			      struct wpa_tdls_peer *peer)
{
	if (!kde->ht_capabilities) {
		wpa_printf(MSG_DEBUG, "TDLS: No supported ht capabilities "
			   "received");
		return 0;
	}

	if (!peer->ht_capabilities) {
		peer->ht_capabilities =
                        os_zalloc(sizeof(struct ieee80211_ht_capabilities));
		if (peer->ht_capabilities == NULL)
                        return -1;
	}

	os_memcpy(peer->ht_capabilities, kde->ht_capabilities,
                  sizeof(struct ieee80211_ht_capabilities));
	wpa_hexdump(MSG_DEBUG, "TDLS: Peer HT capabilities",
		    (u8 *) peer->ht_capabilities,
		    sizeof(struct ieee80211_ht_capabilities));

	return 0;
}