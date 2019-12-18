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
 int /*<<< orphan*/  EAP_PAX_MAC_LEN ; 
 int SHA1_MAC_LEN ; 
 scalar_t__ hmac_sha1_vector (scalar_t__ const*,size_t,size_t,scalar_t__ const**,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 

int eap_pax_mac(u8 mac_id, const u8 *key, size_t key_len,
		const u8 *data1, size_t data1_len,
		const u8 *data2, size_t data2_len,
		const u8 *data3, size_t data3_len,
		u8 *mac)
{
	u8 hash[SHA1_MAC_LEN];
	const u8 *addr[3];
	size_t len[3];
	size_t count;

	/* TODO: add support for EAP_PAX_HMAC_SHA256_128 */
	if (mac_id != EAP_PAX_MAC_HMAC_SHA1_128)
		return -1;

	addr[0] = data1;
	len[0] = data1_len;
	addr[1] = data2;
	len[1] = data2_len;
	addr[2] = data3;
	len[2] = data3_len;

	count = (data1 ? 1 : 0) + (data2 ? 1 : 0) + (data3 ? 1 : 0);
	if (hmac_sha1_vector(key, key_len, count, addr, len, hash) < 0)
		return -1;
	os_memcpy(mac, hash, EAP_PAX_MAC_LEN);

	return 0;
}