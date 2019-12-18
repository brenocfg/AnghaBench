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
 size_t AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  aes_encrypt (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xor_aes_block (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void aes_ccm_encr(void *aes, size_t L, const u8 *in, size_t len, u8 *out,
			 u8 *a)
{
	size_t last = len % AES_BLOCK_SIZE;
	size_t i;

	/* crypt = msg XOR (S_1 | S_2 | ... | S_n) */
	for (i = 1; i <= len / AES_BLOCK_SIZE; i++) {
		WPA_PUT_BE16(&a[AES_BLOCK_SIZE - 2], i);
		/* S_i = E(K, A_i) */
		aes_encrypt(aes, a, out);
		xor_aes_block(out, in);
		out += AES_BLOCK_SIZE;
		in += AES_BLOCK_SIZE;
	}
	if (last) {
		WPA_PUT_BE16(&a[AES_BLOCK_SIZE - 2], i);
		aes_encrypt(aes, a, out);
		/* XOR zero-padded last block */
		for (i = 0; i < last; i++)
			*out++ ^= *in++;
	}
}