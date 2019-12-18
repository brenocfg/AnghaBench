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
struct TYPE_2__ {int hdr; } ;
struct talitos_edesc {TYPE_1__ desc; } ;
struct talitos_ctx {int desc_hdr_template; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {unsigned int nbytes; } ;

/* Variables and functions */
 int DESC_HDR_DIR_INBOUND ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct talitos_edesc*) ; 
 int PTR_ERR (struct talitos_edesc*) ; 
 int /*<<< orphan*/  ablkcipher_done ; 
 struct talitos_edesc* ablkcipher_edesc_alloc (struct ablkcipher_request*,int) ; 
 int common_nonsnoop (struct talitos_edesc*,struct ablkcipher_request*,int /*<<< orphan*/ ) ; 
 struct talitos_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 unsigned int crypto_tfm_alg_blocksize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ablkcipher_decrypt(struct ablkcipher_request *areq)
{
	struct crypto_ablkcipher *cipher = crypto_ablkcipher_reqtfm(areq);
	struct talitos_ctx *ctx = crypto_ablkcipher_ctx(cipher);
	struct talitos_edesc *edesc;
	unsigned int blocksize =
			crypto_tfm_alg_blocksize(crypto_ablkcipher_tfm(cipher));

	if (!areq->nbytes)
		return 0;

	if (areq->nbytes % blocksize)
		return -EINVAL;

	/* allocate extended descriptor */
	edesc = ablkcipher_edesc_alloc(areq, false);
	if (IS_ERR(edesc))
		return PTR_ERR(edesc);

	edesc->desc.hdr = ctx->desc_hdr_template | DESC_HDR_DIR_INBOUND;

	return common_nonsnoop(edesc, areq, ablkcipher_done);
}