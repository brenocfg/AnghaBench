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
struct skcipher_request {int /*<<< orphan*/  cryptlen; } ;
struct skcipher_edesc {int /*<<< orphan*/  drv_req; } ;
struct crypto_skcipher {int dummy; } ;
struct caam_ctx {int /*<<< orphan*/  qidev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINPROGRESS ; 
 scalar_t__ IS_ERR (struct skcipher_edesc*) ; 
 int PTR_ERR (struct skcipher_edesc*) ; 
 int /*<<< orphan*/  caam_congested ; 
 int caam_qi_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct caam_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  qi_cache_free (struct skcipher_edesc*) ; 
 struct skcipher_edesc* skcipher_edesc_alloc (struct skcipher_request*,int) ; 
 int /*<<< orphan*/  skcipher_unmap (int /*<<< orphan*/ ,struct skcipher_edesc*,struct skcipher_request*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int skcipher_crypt(struct skcipher_request *req, bool encrypt)
{
	struct skcipher_edesc *edesc;
	struct crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	struct caam_ctx *ctx = crypto_skcipher_ctx(skcipher);
	int ret;

	if (!req->cryptlen)
		return 0;

	if (unlikely(caam_congested))
		return -EAGAIN;

	/* allocate extended descriptor */
	edesc = skcipher_edesc_alloc(req, encrypt);
	if (IS_ERR(edesc))
		return PTR_ERR(edesc);

	ret = caam_qi_enqueue(ctx->qidev, &edesc->drv_req);
	if (!ret) {
		ret = -EINPROGRESS;
	} else {
		skcipher_unmap(ctx->qidev, edesc, req);
		qi_cache_free(edesc);
	}

	return ret;
}