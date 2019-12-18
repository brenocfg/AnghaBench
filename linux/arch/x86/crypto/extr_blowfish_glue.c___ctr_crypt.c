#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_7__ {scalar_t__ addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {scalar_t__ addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct skcipher_walk {unsigned int nbytes; scalar_t__ iv; TYPE_4__ dst; TYPE_2__ src; } ;
struct bf_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 unsigned int BF_BLOCK_SIZE ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blowfish_enc_blk_xor (struct bf_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blowfish_enc_blk_xor_4way (struct bf_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int __ctr_crypt(struct bf_ctx *ctx, struct skcipher_walk *walk)
{
	unsigned int bsize = BF_BLOCK_SIZE;
	unsigned int nbytes = walk->nbytes;
	u64 *src = (u64 *)walk->src.virt.addr;
	u64 *dst = (u64 *)walk->dst.virt.addr;
	u64 ctrblk = be64_to_cpu(*(__be64 *)walk->iv);
	__be64 ctrblocks[4];

	/* Process four block batch */
	if (nbytes >= bsize * 4) {
		do {
			if (dst != src) {
				dst[0] = src[0];
				dst[1] = src[1];
				dst[2] = src[2];
				dst[3] = src[3];
			}

			/* create ctrblks for parallel encrypt */
			ctrblocks[0] = cpu_to_be64(ctrblk++);
			ctrblocks[1] = cpu_to_be64(ctrblk++);
			ctrblocks[2] = cpu_to_be64(ctrblk++);
			ctrblocks[3] = cpu_to_be64(ctrblk++);

			blowfish_enc_blk_xor_4way(ctx, (u8 *)dst,
						  (u8 *)ctrblocks);

			src += 4;
			dst += 4;
		} while ((nbytes -= bsize * 4) >= bsize * 4);

		if (nbytes < bsize)
			goto done;
	}

	/* Handle leftovers */
	do {
		if (dst != src)
			*dst = *src;

		ctrblocks[0] = cpu_to_be64(ctrblk++);

		blowfish_enc_blk_xor(ctx, (u8 *)dst, (u8 *)ctrblocks);

		src += 1;
		dst += 1;
	} while ((nbytes -= bsize) >= bsize);

done:
	*(__be64 *)walk->iv = cpu_to_be64(ctrblk);
	return nbytes;
}