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
typedef  int /*<<< orphan*/  const u8 ;
struct TYPE_2__ {int /*<<< orphan*/  const* tk; int /*<<< orphan*/  const* kck; } ;
struct wpa_tdls_peer {int tpk_set; TYPE_1__ tpk; int /*<<< orphan*/  const* addr; int /*<<< orphan*/  const* inonce; int /*<<< orphan*/  const* rnonce; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int SHA256_MAC_LEN ; 
 int WPA_NONCE_LEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  sha256_prf (int /*<<< orphan*/  const*,int,char*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  sha256_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void wpa_tdls_generate_tpk(struct wpa_tdls_peer *peer,
				  const u8 *own_addr, const u8 *bssid)
{
	u8 key_input[SHA256_MAC_LEN];
	const u8 *nonce[2];
	size_t len[2];
	u8 data[3 * ETH_ALEN];

	/* IEEE Std 802.11-2016 12.7.9.2:
	 * TPK-Key-Input = Hash(min(SNonce, ANonce) || max(SNonce, ANonce))
	 * Hash = SHA-256 for TDLS
	 */
	len[0] = WPA_NONCE_LEN;
	len[1] = WPA_NONCE_LEN;
	if (os_memcmp(peer->inonce, peer->rnonce, WPA_NONCE_LEN) < 0) {
		nonce[0] = peer->inonce;
		nonce[1] = peer->rnonce;
	} else {
		nonce[0] = peer->rnonce;
		nonce[1] = peer->inonce;
	}
	wpa_hexdump(MSG_DEBUG, "TDLS: min(Nonce)", nonce[0], WPA_NONCE_LEN);
	wpa_hexdump(MSG_DEBUG, "TDLS: max(Nonce)", nonce[1], WPA_NONCE_LEN);
	sha256_vector(2, nonce, len, key_input);
	wpa_hexdump_key(MSG_DEBUG, "TDLS: TPK-Key-Input",
			key_input, SHA256_MAC_LEN);

	/*
	 * TPK = KDF-Hash-Length(TPK-Key-Input, "TDLS PMK",
	 *	min(MAC_I, MAC_R) || max(MAC_I, MAC_R) || BSSID)
	 */

	if (os_memcmp(own_addr, peer->addr, ETH_ALEN) < 0) {
		os_memcpy(data, own_addr, ETH_ALEN);
		os_memcpy(data + ETH_ALEN, peer->addr, ETH_ALEN);
	} else {
		os_memcpy(data, peer->addr, ETH_ALEN);
		os_memcpy(data + ETH_ALEN, own_addr, ETH_ALEN);
	}
	os_memcpy(data + 2 * ETH_ALEN, bssid, ETH_ALEN);
	wpa_hexdump(MSG_DEBUG, "TDLS: KDF Context", data, sizeof(data));

	sha256_prf(key_input, SHA256_MAC_LEN, "TDLS PMK", data, sizeof(data),
		   (u8 *) &peer->tpk, sizeof(peer->tpk));
	wpa_hexdump_key(MSG_DEBUG, "TDLS: TPK-KCK",
			peer->tpk.kck, sizeof(peer->tpk.kck));
	wpa_hexdump_key(MSG_DEBUG, "TDLS: TPK-TK",
			peer->tpk.tk, sizeof(peer->tpk.tk));
	peer->tpk_set = 1;
}