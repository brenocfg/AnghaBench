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
typedef  int u8 ;

/* Variables and functions */
 int SHA1_MAC_LEN ; 
 int hmac_sha1_vector (int const*,size_t,int,int const**,size_t*,int*) ; 
 int /*<<< orphan*/  os_memcpy (int*,int*,size_t) ; 

__attribute__((used)) static int eap_eke_prf_hmac_sha1(const u8 *key, size_t key_len, const u8 *data,
				 size_t data_len, u8 *res, size_t len)
{
	u8 hash[SHA1_MAC_LEN];
	u8 idx;
	const u8 *addr[3];
	size_t vlen[3];
	int ret;

	idx = 0;
	addr[0] = hash;
	vlen[0] = SHA1_MAC_LEN;
	addr[1] = data;
	vlen[1] = data_len;
	addr[2] = &idx;
	vlen[2] = 1;

	while (len > 0) {
		idx++;
		if (idx == 1)
			ret = hmac_sha1_vector(key, key_len, 2, &addr[1],
					       &vlen[1], hash);
		else
			ret = hmac_sha1_vector(key, key_len, 3, addr, vlen,
					       hash);
		if (ret < 0)
			return -1;
		if (len > SHA1_MAC_LEN) {
			os_memcpy(res, hash, SHA1_MAC_LEN);
			res += SHA1_MAC_LEN;
			len -= SHA1_MAC_LEN;
		} else {
			os_memcpy(res, hash, len);
			len = 0;
		}
	}

	return 0;
}