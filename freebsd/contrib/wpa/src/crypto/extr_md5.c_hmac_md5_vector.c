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
typedef  int /*<<< orphan*/  tk ;
typedef  int /*<<< orphan*/  k_pad ;

/* Variables and functions */
 size_t MD5_MAC_LEN ; 
 int md5_vector (int,int const**,size_t*,int*) ; 
 int /*<<< orphan*/  os_memcpy (int*,int const*,size_t) ; 
 int /*<<< orphan*/  os_memset (int*,int /*<<< orphan*/ ,int) ; 

int hmac_md5_vector(const u8 *key, size_t key_len, size_t num_elem,
		    const u8 *addr[], const size_t *len, u8 *mac)
{
	u8 k_pad[64]; /* padding - key XORd with ipad/opad */
	u8 tk[16];
	const u8 *_addr[6];
	size_t i, _len[6];
	int res;

	if (num_elem > 5) {
		/*
		 * Fixed limit on the number of fragments to avoid having to
		 * allocate memory (which could fail).
		 */
		return -1;
	}

        /* if key is longer than 64 bytes reset it to key = MD5(key) */
        if (key_len > 64) {
		if (md5_vector(1, &key, &key_len, tk))
			return -1;
		key = tk;
		key_len = 16;
        }

	/* the HMAC_MD5 transform looks like:
	 *
	 * MD5(K XOR opad, MD5(K XOR ipad, text))
	 *
	 * where K is an n byte key
	 * ipad is the byte 0x36 repeated 64 times
	 * opad is the byte 0x5c repeated 64 times
	 * and text is the data being protected */

	/* start out by storing key in ipad */
	os_memset(k_pad, 0, sizeof(k_pad));
	os_memcpy(k_pad, key, key_len);

	/* XOR key with ipad values */
	for (i = 0; i < 64; i++)
		k_pad[i] ^= 0x36;

	/* perform inner MD5 */
	_addr[0] = k_pad;
	_len[0] = 64;
	for (i = 0; i < num_elem; i++) {
		_addr[i + 1] = addr[i];
		_len[i + 1] = len[i];
	}
	if (md5_vector(1 + num_elem, _addr, _len, mac))
		return -1;

	os_memset(k_pad, 0, sizeof(k_pad));
	os_memcpy(k_pad, key, key_len);
	/* XOR key with opad values */
	for (i = 0; i < 64; i++)
		k_pad[i] ^= 0x5c;

	/* perform outer MD5 */
	_addr[0] = k_pad;
	_len[0] = 64;
	_addr[1] = mac;
	_len[1] = MD5_MAC_LEN;
	res = md5_vector(2, _addr, _len, mac);
	os_memset(k_pad, 0, sizeof(k_pad));
	os_memset(tk, 0, sizeof(tk));
	return res;
}