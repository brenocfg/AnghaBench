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

/* Variables and functions */
#define  EAP_GPSK_CIPHER_AES 129 
#define  EAP_GPSK_CIPHER_SHA256 128 
 int EAP_GPSK_RAND_LEN ; 
 int EAP_GPSK_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int eap_gpsk_derive_keys_aes (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,size_t*) ; 
 int eap_gpsk_derive_keys_sha256 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int eap_gpsk_derive_keys(const u8 *psk, size_t psk_len, int vendor,
			 int specifier,
			 const u8 *rand_peer, const u8 *rand_server,
			 const u8 *id_peer, size_t id_peer_len,
			 const u8 *id_server, size_t id_server_len,
			 u8 *msk, u8 *emsk, u8 *sk, size_t *sk_len,
			 u8 *pk, size_t *pk_len)
{
	u8 *seed, *pos;
	int ret;

	wpa_printf(MSG_DEBUG, "EAP-GPSK: Deriving keys (%d:%d)",
		   vendor, specifier);

	if (vendor != EAP_GPSK_VENDOR_IETF)
		return -1;

	wpa_hexdump_key(MSG_DEBUG, "EAP-GPSK: PSK", psk, psk_len);

	/* Seed = RAND_Peer || ID_Peer || RAND_Server || ID_Server */
	seed = os_malloc(2 * EAP_GPSK_RAND_LEN + id_server_len + id_peer_len);
	if (seed == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Failed to allocate memory "
			   "for key derivation");
		return -1;
	}

	pos = seed;
	os_memcpy(pos, rand_peer, EAP_GPSK_RAND_LEN);
	pos += EAP_GPSK_RAND_LEN;
	os_memcpy(pos, id_peer, id_peer_len);
	pos += id_peer_len;
	os_memcpy(pos, rand_server, EAP_GPSK_RAND_LEN);
	pos += EAP_GPSK_RAND_LEN;
	os_memcpy(pos, id_server, id_server_len);
	pos += id_server_len;
	wpa_hexdump(MSG_DEBUG, "EAP-GPSK: Seed", seed, pos - seed);

	switch (specifier) {
	case EAP_GPSK_CIPHER_AES:
		ret = eap_gpsk_derive_keys_aes(psk, psk_len, seed, pos - seed,
					       msk, emsk, sk, sk_len,
					       pk, pk_len);
		break;
#ifdef EAP_GPSK_SHA256
	case EAP_GPSK_CIPHER_SHA256:
		ret = eap_gpsk_derive_keys_sha256(psk, psk_len, seed,
						  pos - seed,
						  msk, emsk, sk, sk_len);
		break;
#endif /* EAP_GPSK_SHA256 */
	default:
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Unknown cipher %d:%d used in "
			   "key derivation", vendor, specifier);
		ret = -1;
		break;
	}

	os_free(seed);

	return ret;
}