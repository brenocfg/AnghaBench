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
struct talitos_edesc {int dummy; } ;
struct talitos_ctx {int /*<<< orphan*/  dev; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct aead_request {unsigned int cryptlen; TYPE_1__ base; int /*<<< orphan*/  assoclen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct talitos_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 unsigned int crypto_aead_ivsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 struct talitos_edesc* talitos_edesc_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct talitos_edesc *aead_edesc_alloc(struct aead_request *areq, u8 *iv,
					      int icv_stashing, bool encrypt)
{
	struct crypto_aead *authenc = crypto_aead_reqtfm(areq);
	unsigned int authsize = crypto_aead_authsize(authenc);
	struct talitos_ctx *ctx = crypto_aead_ctx(authenc);
	unsigned int ivsize = crypto_aead_ivsize(authenc);
	unsigned int cryptlen = areq->cryptlen - (encrypt ? 0 : authsize);

	return talitos_edesc_alloc(ctx->dev, areq->src, areq->dst,
				   iv, areq->assoclen, cryptlen,
				   authsize, ivsize, icv_stashing,
				   areq->base.flags, encrypt);
}