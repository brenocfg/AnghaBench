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
 int aes_s2v (int const*,size_t,size_t,int const**,size_t*,int*) ; 
 scalar_t__ os_memcmp (int*,int const*,int) ; 
 int /*<<< orphan*/  os_memcpy (int*,int const*,size_t) ; 

int aes_siv_decrypt(const u8 *key, size_t key_len,
		    const u8 *iv_crypt, size_t iv_c_len,
		    size_t num_elem, const u8 *addr[], const size_t *len,
		    u8 *out)
{
	const u8 *_addr[6];
	size_t _len[6];
	const u8 *k1, *k2;
	size_t crypt_len;
	size_t i;
	int ret;
	u8 iv[AES_BLOCK_SIZE];
	u8 check[AES_BLOCK_SIZE];

	if (iv_c_len < AES_BLOCK_SIZE || num_elem > ARRAY_SIZE(_addr) - 1 ||
	    (key_len != 32 && key_len != 48 && key_len != 64))
		return -1;
	crypt_len = iv_c_len - AES_BLOCK_SIZE;
	key_len /= 2;
	k1 = key;
	k2 = key + key_len;

	for (i = 0; i < num_elem; i++) {
		_addr[i] = addr[i];
		_len[i] = len[i];
	}
	_addr[num_elem] = out;
	_len[num_elem] = crypt_len;

	os_memcpy(iv, iv_crypt, AES_BLOCK_SIZE);
	os_memcpy(out, iv_crypt + AES_BLOCK_SIZE, crypt_len);

	iv[8] &= 0x7f;
	iv[12] &= 0x7f;

	ret = aes_ctr_encrypt(k2, key_len, iv, out, crypt_len);
	if (ret)
		return ret;

	ret = aes_s2v(k1, key_len, num_elem + 1, _addr, _len, check);
	if (ret)
		return ret;
	if (os_memcmp(check, iv_crypt, AES_BLOCK_SIZE) == 0)
		return 0;

	return -1;
}