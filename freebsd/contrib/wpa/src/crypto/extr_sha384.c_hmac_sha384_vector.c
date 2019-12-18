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
typedef  unsigned char u8 ;
typedef  int /*<<< orphan*/  k_pad ;

/* Variables and functions */
 size_t SHA384_MAC_LEN ; 
 int /*<<< orphan*/  os_memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  os_memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int sha384_vector (int,unsigned char const**,size_t*,unsigned char*) ; 

int hmac_sha384_vector(const u8 *key, size_t key_len, size_t num_elem,
		       const u8 *addr[], const size_t *len, u8 *mac)
{
	unsigned char k_pad[128]; /* padding - key XORd with ipad/opad */
	unsigned char tk[48];
	const u8 *_addr[6];
	size_t _len[6], i;

	if (num_elem > 5) {
		/*
		 * Fixed limit on the number of fragments to avoid having to
		 * allocate memory (which could fail).
		 */
		return -1;
	}

	/* if key is longer than 128 bytes reset it to key = SHA384(key) */
	if (key_len > 128) {
		if (sha384_vector(1, &key, &key_len, tk) < 0)
			return -1;
		key = tk;
		key_len = 48;
	}

	/* the HMAC_SHA384 transform looks like:
	 *
	 * SHA384(K XOR opad, SHA384(K XOR ipad, text))
	 *
	 * where K is an n byte key
	 * ipad is the byte 0x36 repeated 128 times
	 * opad is the byte 0x5c repeated 128 times
	 * and text is the data being protected */

	/* start out by storing key in ipad */
	os_memset(k_pad, 0, sizeof(k_pad));
	os_memcpy(k_pad, key, key_len);
	/* XOR key with ipad values */
	for (i = 0; i < 128; i++)
		k_pad[i] ^= 0x36;

	/* perform inner SHA384 */
	_addr[0] = k_pad;
	_len[0] = 128;
	for (i = 0; i < num_elem; i++) {
		_addr[i + 1] = addr[i];
		_len[i + 1] = len[i];
	}
	if (sha384_vector(1 + num_elem, _addr, _len, mac) < 0)
		return -1;

	os_memset(k_pad, 0, sizeof(k_pad));
	os_memcpy(k_pad, key, key_len);
	/* XOR key with opad values */
	for (i = 0; i < 128; i++)
		k_pad[i] ^= 0x5c;

	/* perform outer SHA384 */
	_addr[0] = k_pad;
	_len[0] = 128;
	_addr[1] = mac;
	_len[1] = SHA384_MAC_LEN;
	return sha384_vector(2, _addr, _len, mac);
}