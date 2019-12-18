#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spacc_req {int dummy; } ;
struct spacc_engine {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  iv_offs; int /*<<< orphan*/  key_offs; struct spacc_engine* engine; int /*<<< orphan*/  flags; } ;
struct spacc_aead_ctx {int /*<<< orphan*/  sw_cipher; TYPE_2__ generic; } ;
struct spacc_aead {int /*<<< orphan*/  iv_offs; int /*<<< orphan*/  key_offs; int /*<<< orphan*/  type; struct spacc_engine* engine; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  cra_name; } ;
struct aead_alg {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct aead_alg* crypto_aead_alg (struct crypto_aead*) ; 
 struct spacc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 scalar_t__ crypto_aead_reqsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_set_reqsize (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_aead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int,scalar_t__) ; 
 struct spacc_aead* to_spacc_aead (struct aead_alg*) ; 

__attribute__((used)) static int spacc_aead_cra_init(struct crypto_aead *tfm)
{
	struct spacc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_alg *alg = crypto_aead_alg(tfm);
	struct spacc_aead *spacc_alg = to_spacc_aead(alg);
	struct spacc_engine *engine = spacc_alg->engine;

	ctx->generic.flags = spacc_alg->type;
	ctx->generic.engine = engine;
	ctx->sw_cipher = crypto_alloc_aead(alg->base.cra_name, 0,
					   CRYPTO_ALG_NEED_FALLBACK);
	if (IS_ERR(ctx->sw_cipher))
		return PTR_ERR(ctx->sw_cipher);
	ctx->generic.key_offs = spacc_alg->key_offs;
	ctx->generic.iv_offs = spacc_alg->iv_offs;

	crypto_aead_set_reqsize(
		tfm,
		max(sizeof(struct spacc_req),
		    sizeof(struct aead_request) +
		    crypto_aead_reqsize(ctx->sw_cipher)));

	return 0;
}