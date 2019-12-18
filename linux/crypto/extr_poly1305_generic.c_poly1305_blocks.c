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
struct poly1305_desc_ctx {int /*<<< orphan*/  r; int /*<<< orphan*/  h; int /*<<< orphan*/  sset; } ;

/* Variables and functions */
 unsigned int POLY1305_BLOCK_SIZE ; 
 unsigned int crypto_poly1305_setdesckey (struct poly1305_desc_ctx*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  poly1305_blocks_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void poly1305_blocks(struct poly1305_desc_ctx *dctx,
			    const u8 *src, unsigned int srclen, u32 hibit)
{
	unsigned int datalen;

	if (unlikely(!dctx->sset)) {
		datalen = crypto_poly1305_setdesckey(dctx, src, srclen);
		src += srclen - datalen;
		srclen = datalen;
	}

	poly1305_blocks_internal(&dctx->h, &dctx->r,
				 src, srclen / POLY1305_BLOCK_SIZE, hibit);
}