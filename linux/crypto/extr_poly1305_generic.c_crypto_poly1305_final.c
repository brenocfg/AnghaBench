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
typedef  int u64 ;
struct shash_desc {int dummy; } ;
struct poly1305_desc_ctx {int buflen; int* buf; int* s; int /*<<< orphan*/  h; int /*<<< orphan*/  sset; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ENOKEY ; 
 scalar_t__ POLY1305_BLOCK_SIZE ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  poly1305_blocks (struct poly1305_desc_ctx*,int*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poly1305_core_emit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ *) ; 
 struct poly1305_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 
 scalar_t__ unlikely (int) ; 

int crypto_poly1305_final(struct shash_desc *desc, u8 *dst)
{
	struct poly1305_desc_ctx *dctx = shash_desc_ctx(desc);
	__le32 digest[4];
	u64 f = 0;

	if (unlikely(!dctx->sset))
		return -ENOKEY;

	if (unlikely(dctx->buflen)) {
		dctx->buf[dctx->buflen++] = 1;
		memset(dctx->buf + dctx->buflen, 0,
		       POLY1305_BLOCK_SIZE - dctx->buflen);
		poly1305_blocks(dctx, dctx->buf, POLY1305_BLOCK_SIZE, 0);
	}

	poly1305_core_emit(&dctx->h, digest);

	/* mac = (h + s) % (2^128) */
	f = (f >> 32) + le32_to_cpu(digest[0]) + dctx->s[0];
	put_unaligned_le32(f, dst + 0);
	f = (f >> 32) + le32_to_cpu(digest[1]) + dctx->s[1];
	put_unaligned_le32(f, dst + 4);
	f = (f >> 32) + le32_to_cpu(digest[2]) + dctx->s[2];
	put_unaligned_le32(f, dst + 8);
	f = (f >> 32) + le32_to_cpu(digest[3]) + dctx->s[3];
	put_unaligned_le32(f, dst + 12);

	return 0;
}