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
typedef  int u32 ;
struct crypto_sm4_ctx {int* rkey_enc; int* rkey_dec; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SM4_KEY_SIZE ; 
 int* ck ; 
 int* fk ; 
 int get_unaligned_be32 (int const*) ; 
 int sm4_key_sub (int) ; 

int crypto_sm4_expand_key(struct crypto_sm4_ctx *ctx, const u8 *in_key,
			  unsigned int key_len)
{
	u32 rk[4], t;
	const u32 *key = (u32 *)in_key;
	int i;

	if (key_len != SM4_KEY_SIZE)
		return -EINVAL;

	for (i = 0; i < 4; ++i)
		rk[i] = get_unaligned_be32(&key[i]) ^ fk[i];

	for (i = 0; i < 32; ++i) {
		t = rk[0] ^ sm4_key_sub(rk[1] ^ rk[2] ^ rk[3] ^ ck[i]);
		ctx->rkey_enc[i] = t;
		rk[0] = rk[1];
		rk[1] = rk[2];
		rk[2] = rk[3];
		rk[3] = t;
	}

	for (i = 0; i < 32; ++i)
		ctx->rkey_dec[i] = ctx->rkey_enc[31 - i];

	return 0;
}