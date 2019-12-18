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
 int /*<<< orphan*/  aes_encrypt (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xor_aes_block (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void aes_ccm_auth(void *aes, const u8 *data, size_t len, u8 *x)
{
	size_t last = len % AES_BLOCK_SIZE;
	size_t i;

	for (i = 0; i < len / AES_BLOCK_SIZE; i++) {
		/* X_i+1 = E(K, X_i XOR B_i) */
		xor_aes_block(x, data);
		data += AES_BLOCK_SIZE;
		aes_encrypt(aes, x, x);
	}
	if (last) {
		/* XOR zero-padded last block */
		for (i = 0; i < last; i++)
			x[i] ^= *data++;
		aes_encrypt(aes, x, x);
	}
}