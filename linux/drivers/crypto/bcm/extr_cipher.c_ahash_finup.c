#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  tfm; } ;
typedef  TYPE_2__ u8 ;
struct iproc_ctx_s {TYPE_2__* shash; } ;
struct crypto_ahash {int dummy; } ;
struct TYPE_8__ {int flags; } ;
struct ahash_request {int /*<<< orphan*/  result; int /*<<< orphan*/  nbytes; scalar_t__ src; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __ahash_finup (struct ahash_request*) ; 
 struct iproc_ctx_s* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 
 int crypto_shash_finup (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (scalar_t__,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int sg_nents (scalar_t__) ; 
 scalar_t__ spu_no_incr_hash (struct iproc_ctx_s*) ; 

__attribute__((used)) static int ahash_finup(struct ahash_request *req)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct iproc_ctx_s *ctx = crypto_ahash_ctx(tfm);
	u8 *tmpbuf;
	int ret;
	int nents;
	gfp_t gfp;

	if (spu_no_incr_hash(ctx)) {
		/*
		 * If we get an incremental hashing request and it's not
		 * supported by the hardware, we need to handle it in software
		 * by calling synchronous hash functions.
		 */
		if (req->src) {
			nents = sg_nents(req->src);
		} else {
			ret = -EINVAL;
			goto ahash_finup_exit;
		}

		/* Copy data from req scatterlist to tmp buffer */
		gfp = (req->base.flags & (CRYPTO_TFM_REQ_MAY_BACKLOG |
		       CRYPTO_TFM_REQ_MAY_SLEEP)) ? GFP_KERNEL : GFP_ATOMIC;
		tmpbuf = kmalloc(req->nbytes, gfp);
		if (!tmpbuf) {
			ret = -ENOMEM;
			goto ahash_finup_exit;
		}

		if (sg_copy_to_buffer(req->src, nents, tmpbuf, req->nbytes) !=
				req->nbytes) {
			ret = -EINVAL;
			goto ahash_finup_free;
		}

		/* Call synchronous update */
		ret = crypto_shash_finup(ctx->shash, tmpbuf, req->nbytes,
					 req->result);
	} else {
		/* Otherwise call the internal function which uses SPU hw */
		return __ahash_finup(req);
	}
ahash_finup_free:
	kfree(tmpbuf);

ahash_finup_exit:
	/* Done with hash, can deallocate it now */
	crypto_free_shash(ctx->shash->tfm);
	kfree(ctx->shash);
	return ret;
}