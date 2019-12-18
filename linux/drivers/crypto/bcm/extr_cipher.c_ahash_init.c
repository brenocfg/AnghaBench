#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iproc_ctx_s {scalar_t__ authkeylen; TYPE_2__* shash; int /*<<< orphan*/  authkey; } ;
struct crypto_shash {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct TYPE_5__ {int flags; } ;
struct ahash_request {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_6__ {struct crypto_shash* tfm; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int PTR_ERR (struct crypto_shash*) ; 
 int __ahash_init (struct ahash_request*) ; 
 struct iproc_ctx_s* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 struct crypto_shash* crypto_alloc_shash (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (struct crypto_shash*) ; 
 scalar_t__ crypto_shash_descsize (struct crypto_shash*) ; 
 int crypto_shash_init (TYPE_2__*) ; 
 int crypto_shash_setkey (struct crypto_shash*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* crypto_tfm_alg_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ spu_no_incr_hash (struct iproc_ctx_s*) ; 

__attribute__((used)) static int ahash_init(struct ahash_request *req)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct iproc_ctx_s *ctx = crypto_ahash_ctx(tfm);
	const char *alg_name;
	struct crypto_shash *hash;
	int ret;
	gfp_t gfp;

	if (spu_no_incr_hash(ctx)) {
		/*
		 * If we get an incremental hashing request and it's not
		 * supported by the hardware, we need to handle it in software
		 * by calling synchronous hash functions.
		 */
		alg_name = crypto_tfm_alg_name(crypto_ahash_tfm(tfm));
		hash = crypto_alloc_shash(alg_name, 0, 0);
		if (IS_ERR(hash)) {
			ret = PTR_ERR(hash);
			goto err;
		}

		gfp = (req->base.flags & (CRYPTO_TFM_REQ_MAY_BACKLOG |
		       CRYPTO_TFM_REQ_MAY_SLEEP)) ? GFP_KERNEL : GFP_ATOMIC;
		ctx->shash = kmalloc(sizeof(*ctx->shash) +
				     crypto_shash_descsize(hash), gfp);
		if (!ctx->shash) {
			ret = -ENOMEM;
			goto err_hash;
		}
		ctx->shash->tfm = hash;

		/* Set the key using data we already have from setkey */
		if (ctx->authkeylen > 0) {
			ret = crypto_shash_setkey(hash, ctx->authkey,
						  ctx->authkeylen);
			if (ret)
				goto err_shash;
		}

		/* Initialize hash w/ this key and other params */
		ret = crypto_shash_init(ctx->shash);
		if (ret)
			goto err_shash;
	} else {
		/* Otherwise call the internal function which uses SPU hw */
		ret = __ahash_init(req);
	}

	return ret;

err_shash:
	kfree(ctx->shash);
err_hash:
	crypto_free_shash(hash);
err:
	return ret;
}