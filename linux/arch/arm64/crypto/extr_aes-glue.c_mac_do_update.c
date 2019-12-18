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
struct crypto_aes_ctx {int key_length; int /*<<< orphan*/  key_enc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  aes_encrypt (struct crypto_aes_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aes_mac_update (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ crypto_simd_usable () ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_neon_begin () ; 
 int /*<<< orphan*/  kernel_neon_end () ; 

__attribute__((used)) static void mac_do_update(struct crypto_aes_ctx *ctx, u8 const in[], int blocks,
			  u8 dg[], int enc_before, int enc_after)
{
	int rounds = 6 + ctx->key_length / 4;

	if (crypto_simd_usable()) {
		kernel_neon_begin();
		aes_mac_update(in, ctx->key_enc, rounds, blocks, dg, enc_before,
			       enc_after);
		kernel_neon_end();
	} else {
		if (enc_before)
			aes_encrypt(ctx, dg, dg);

		while (blocks--) {
			crypto_xor(dg, in, AES_BLOCK_SIZE);
			in += AES_BLOCK_SIZE;

			if (blocks || enc_after)
				aes_encrypt(ctx, dg, dg);
		}
	}
}