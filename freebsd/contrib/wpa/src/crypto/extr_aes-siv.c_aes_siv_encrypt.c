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
 int AES_BLOCK_SIZE ; 
 int ARRAY_SIZE (int const**) ; 
 int aes_ctr_encrypt (int const*,size_t,int*,int*,size_t) ; 
 scalar_t__ aes_s2v (int const*,size_t,size_t,int const**,size_t*,int*) ; 
 int /*<<< orphan*/  os_memcpy (int*,int const*,size_t) ; 

int aes_siv_encrypt(const u8 *key, size_t key_len,
		    const u8 *pw, size_t pwlen,
		    size_t num_elem, const u8 *addr[], const size_t *len,
		    u8 *out)
{
	const u8 *_addr[6];
	size_t _len[6];
	const u8 *k1, *k2;
	u8 v[AES_BLOCK_SIZE];
	size_t i;
	u8 *iv, *crypt_pw;

	if (num_elem > ARRAY_SIZE(_addr) - 1 ||
	    (key_len != 32 && key_len != 48 && key_len != 64))
		return -1;

	key_len /= 2;
	k1 = key;
	k2 = key + key_len;

	for (i = 0; i < num_elem; i++) {
		_addr[i] = addr[i];
		_len[i] = len[i];
	}
	_addr[num_elem] = pw;
	_len[num_elem] = pwlen;

	if (aes_s2v(k1, key_len, num_elem + 1, _addr, _len, v))
		return -1;

	iv = out;
	crypt_pw = out + AES_BLOCK_SIZE;

	os_memcpy(iv, v, AES_BLOCK_SIZE);
	os_memcpy(crypt_pw, pw, pwlen);

	/* zero out 63rd and 31st bits of ctr (from right) */
	v[8] &= 0x7f;
	v[12] &= 0x7f;
	return aes_ctr_encrypt(k2, key_len, v, crypt_pw, pwlen);
}