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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ EAP_PAX_MAC_HMAC_SHA1_128 ; 
 size_t EAP_PAX_MAC_LEN ; 
 int SHA1_MAC_LEN ; 
 scalar_t__ hmac_sha1_vector (scalar_t__ const*,size_t,int,scalar_t__ const**,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__*,scalar_t__*,size_t) ; 
 size_t os_strlen (char const*) ; 

int eap_pax_kdf(u8 mac_id, const u8 *key, size_t key_len,
		const char *identifier,
		const u8 *entropy, size_t entropy_len,
		size_t output_len, u8 *output)
{
	u8 mac[SHA1_MAC_LEN];
	u8 counter, *pos;
	const u8 *addr[3];
	size_t len[3];
	size_t num_blocks, left;

	num_blocks = (output_len + EAP_PAX_MAC_LEN - 1) / EAP_PAX_MAC_LEN;
	if (identifier == NULL || num_blocks >= 255)
		return -1;

	/* TODO: add support for EAP_PAX_HMAC_SHA256_128 */
	if (mac_id != EAP_PAX_MAC_HMAC_SHA1_128)
		return -1;

	addr[0] = (const u8 *) identifier;
	len[0] = os_strlen(identifier);
	addr[1] = entropy;
	len[1] = entropy_len;
	addr[2] = &counter;
	len[2] = 1;

	pos = output;
	left = output_len;
	for (counter = 1; counter <= (u8) num_blocks; counter++) {
		size_t clen = left > EAP_PAX_MAC_LEN ? EAP_PAX_MAC_LEN : left;
		if (hmac_sha1_vector(key, key_len, 3, addr, len, mac) < 0)
			return -1;
		os_memcpy(pos, mac, clen);
		pos += clen;
		left -= clen;
	}

	return 0;
}