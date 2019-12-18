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
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  MSG_EXCESSIVE ; 
 int /*<<< orphan*/  aes_encrypt (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* aes_encrypt_init (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void * aes_gcm_init_hash_subkey(const u8 *key, size_t key_len, u8 *H)
{
	void *aes;

	aes = aes_encrypt_init(key, key_len);
	if (aes == NULL)
		return NULL;

	/* Generate hash subkey H = AES_K(0^128) */
	os_memset(H, 0, AES_BLOCK_SIZE);
	aes_encrypt(aes, H, H);
	wpa_hexdump_key(MSG_EXCESSIVE, "Hash subkey H for GHASH",
			H, AES_BLOCK_SIZE);
	return aes;
}