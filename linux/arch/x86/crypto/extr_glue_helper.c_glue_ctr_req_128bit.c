#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const u128 ;
struct TYPE_11__ {int /*<<< orphan*/  const* addr; } ;
struct TYPE_12__ {TYPE_5__ virt; } ;
struct TYPE_7__ {int /*<<< orphan*/  const* addr; } ;
struct TYPE_8__ {TYPE_1__ virt; } ;
struct skcipher_walk {unsigned int nbytes; scalar_t__ iv; TYPE_6__ dst; TYPE_2__ src; } ;
struct skcipher_request {int dummy; } ;
struct common_glue_ctx {unsigned int num_funcs; TYPE_4__* funcs; int /*<<< orphan*/  fpu_blocks_limit; } ;
typedef  int /*<<< orphan*/  le128 ;
typedef  int /*<<< orphan*/  be128 ;
struct TYPE_9__ {int /*<<< orphan*/  (* ctr ) (void*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {unsigned int num_blocks; TYPE_3__ fn_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  be128_to_le128 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* crypto_skcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int glue_fpu_begin (unsigned int const,int /*<<< orphan*/ ,struct skcipher_walk*,int,unsigned int) ; 
 int /*<<< orphan*/  glue_fpu_end (int) ; 
 int /*<<< orphan*/  le128_to_be128 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int skcipher_walk_done (struct skcipher_walk*,unsigned int) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int glue_ctr_req_128bit(const struct common_glue_ctx *gctx,
			struct skcipher_request *req)
{
	void *ctx = crypto_skcipher_ctx(crypto_skcipher_reqtfm(req));
	const unsigned int bsize = 128 / 8;
	struct skcipher_walk walk;
	bool fpu_enabled = false;
	unsigned int nbytes;
	int err;

	err = skcipher_walk_virt(&walk, req, false);

	while ((nbytes = walk.nbytes) >= bsize) {
		const u128 *src = walk.src.virt.addr;
		u128 *dst = walk.dst.virt.addr;
		unsigned int func_bytes, num_blocks;
		unsigned int i;
		le128 ctrblk;

		fpu_enabled = glue_fpu_begin(bsize, gctx->fpu_blocks_limit,
					     &walk, fpu_enabled, nbytes);

		be128_to_le128(&ctrblk, (be128 *)walk.iv);

		for (i = 0; i < gctx->num_funcs; i++) {
			num_blocks = gctx->funcs[i].num_blocks;
			func_bytes = bsize * num_blocks;

			if (nbytes < func_bytes)
				continue;

			/* Process multi-block batch */
			do {
				gctx->funcs[i].fn_u.ctr(ctx, dst, src, &ctrblk);
				src += num_blocks;
				dst += num_blocks;
				nbytes -= func_bytes;
			} while (nbytes >= func_bytes);

			if (nbytes < bsize)
				break;
		}

		le128_to_be128((be128 *)walk.iv, &ctrblk);
		err = skcipher_walk_done(&walk, nbytes);
	}

	glue_fpu_end(fpu_enabled);

	if (nbytes) {
		le128 ctrblk;
		u128 tmp;

		be128_to_le128(&ctrblk, (be128 *)walk.iv);
		memcpy(&tmp, walk.src.virt.addr, nbytes);
		gctx->funcs[gctx->num_funcs - 1].fn_u.ctr(ctx, &tmp, &tmp,
							  &ctrblk);
		memcpy(walk.dst.virt.addr, &tmp, nbytes);
		le128_to_be128((be128 *)walk.iv, &ctrblk);

		err = skcipher_walk_done(&walk, 0);
	}

	return err;
}