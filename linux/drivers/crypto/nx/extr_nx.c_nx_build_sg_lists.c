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
struct scatterlist {int dummy; } ;
struct nx_sg {int dummy; } ;
struct TYPE_7__ {void* outlen; void* inlen; } ;
struct nx_crypto_ctx {struct nx_sg* out_sg; TYPE_3__ op; struct nx_sg* in_sg; TYPE_2__* ap; } ;
struct blkcipher_desc {int /*<<< orphan*/  info; } ;
struct TYPE_5__ {int max_sg_len; } ;
struct TYPE_8__ {TYPE_1__ of; } ;
struct TYPE_6__ {unsigned int sglen; int databytelen; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int NX_PAGE_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 unsigned int min_t (int /*<<< orphan*/ ,unsigned int,int) ; 
 TYPE_4__ nx_driver ; 
 struct nx_sg* nx_walk_and_build (struct nx_sg*,unsigned int,struct scatterlist*,unsigned int,unsigned int*) ; 
 void* trim_sg_list (struct nx_sg*,struct nx_sg*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  u64 ; 

int nx_build_sg_lists(struct nx_crypto_ctx  *nx_ctx,
		      struct blkcipher_desc *desc,
		      struct scatterlist    *dst,
		      struct scatterlist    *src,
		      unsigned int          *nbytes,
		      unsigned int           offset,
		      u8                    *iv)
{
	unsigned int delta = 0;
	unsigned int total = *nbytes;
	struct nx_sg *nx_insg = nx_ctx->in_sg;
	struct nx_sg *nx_outsg = nx_ctx->out_sg;
	unsigned int max_sg_len;

	max_sg_len = min_t(u64, nx_ctx->ap->sglen,
			nx_driver.of.max_sg_len/sizeof(struct nx_sg));
	max_sg_len = min_t(u64, max_sg_len,
			nx_ctx->ap->databytelen/NX_PAGE_SIZE);

	if (iv)
		memcpy(iv, desc->info, AES_BLOCK_SIZE);

	*nbytes = min_t(u64, *nbytes, nx_ctx->ap->databytelen);

	nx_outsg = nx_walk_and_build(nx_outsg, max_sg_len, dst,
					offset, nbytes);
	nx_insg = nx_walk_and_build(nx_insg, max_sg_len, src,
					offset, nbytes);

	if (*nbytes < total)
		delta = *nbytes - (*nbytes & ~(AES_BLOCK_SIZE - 1));

	/* these lengths should be negative, which will indicate to phyp that
	 * the input and output parameters are scatterlists, not linear
	 * buffers */
	nx_ctx->op.inlen = trim_sg_list(nx_ctx->in_sg, nx_insg, delta, nbytes);
	nx_ctx->op.outlen = trim_sg_list(nx_ctx->out_sg, nx_outsg, delta, nbytes);

	return 0;
}