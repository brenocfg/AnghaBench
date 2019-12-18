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
typedef  int /*<<< orphan*/  u32 ;
struct nhpoly1305_key {int /*<<< orphan*/ * nh_key; int /*<<< orphan*/  poly_key; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NHPOLY1305_KEY_SIZE ; 
 int NH_KEY_WORDS ; 
 int /*<<< orphan*/  POLY1305_BLOCK_SIZE ; 
 struct nhpoly1305_key* crypto_shash_ctx (struct crypto_shash*) ; 
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  poly1305_core_setkey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int crypto_nhpoly1305_setkey(struct crypto_shash *tfm,
			     const u8 *key, unsigned int keylen)
{
	struct nhpoly1305_key *ctx = crypto_shash_ctx(tfm);
	int i;

	if (keylen != NHPOLY1305_KEY_SIZE)
		return -EINVAL;

	poly1305_core_setkey(&ctx->poly_key, key);
	key += POLY1305_BLOCK_SIZE;

	for (i = 0; i < NH_KEY_WORDS; i++)
		ctx->nh_key[i] = get_unaligned_le32(key + i * sizeof(u32));

	return 0;
}