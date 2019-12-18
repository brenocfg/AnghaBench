#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct iproc_ctx_s {int /*<<< orphan*/  shash; } ;
struct crypto_ahash {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct ahash_request {int /*<<< orphan*/  nbytes; scalar_t__ src; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __ahash_update (struct ahash_request*) ; 
 struct iproc_ctx_s* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int crypto_shash_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sg_nents (scalar_t__) ; 
 scalar_t__ spu_no_incr_hash (struct iproc_ctx_s*) ; 

__attribute__((used)) static int ahash_update(struct ahash_request *req)
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
		if (req->src)
			nents = sg_nents(req->src);
		else
			return -EINVAL;

		/* Copy data from req scatterlist to tmp buffer */
		gfp = (req->base.flags & (CRYPTO_TFM_REQ_MAY_BACKLOG |
		       CRYPTO_TFM_REQ_MAY_SLEEP)) ? GFP_KERNEL : GFP_ATOMIC;
		tmpbuf = kmalloc(req->nbytes, gfp);
		if (!tmpbuf)
			return -ENOMEM;

		if (sg_copy_to_buffer(req->src, nents, tmpbuf, req->nbytes) !=
				req->nbytes) {
			kfree(tmpbuf);
			return -EINVAL;
		}

		/* Call synchronous update */
		ret = crypto_shash_update(ctx->shash, tmpbuf, req->nbytes);
		kfree(tmpbuf);
	} else {
		/* Otherwise call the internal function which uses SPU hw */
		ret = __ahash_update(req);
	}

	return ret;
}