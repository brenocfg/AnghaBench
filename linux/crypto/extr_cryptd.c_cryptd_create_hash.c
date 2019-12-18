#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int cra_flags; int cra_ctxsize; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; } ;
struct TYPE_5__ {TYPE_1__ base; int /*<<< orphan*/  statesize; int /*<<< orphan*/  digestsize; } ;
struct TYPE_6__ {int /*<<< orphan*/  digest; int /*<<< orphan*/  setkey; int /*<<< orphan*/  import; int /*<<< orphan*/  export; int /*<<< orphan*/  finup; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  init; TYPE_2__ halg; } ;
struct crypto_alg {int cra_flags; } ;
struct shash_alg {TYPE_3__ alg; int /*<<< orphan*/  statesize; int /*<<< orphan*/  digestsize; struct crypto_alg base; } ;
struct rtattr {int dummy; } ;
struct hashd_instance_ctx {int /*<<< orphan*/  spawn; struct cryptd_queue* queue; } ;
struct crypto_template {int dummy; } ;
struct cryptd_queue {int dummy; } ;
struct cryptd_hash_ctx {int dummy; } ;
struct ahash_instance {TYPE_3__ alg; int /*<<< orphan*/  statesize; int /*<<< orphan*/  digestsize; struct crypto_alg base; } ;

/* Variables and functions */
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_INTERNAL ; 
 int CRYPTO_ALG_OPTIONAL_KEY ; 
 scalar_t__ IS_ERR (struct shash_alg*) ; 
 int PTR_ERR (struct shash_alg*) ; 
 int /*<<< orphan*/  ahash_crypto_instance (struct shash_alg*) ; 
 struct hashd_instance_ctx* ahash_instance_ctx (struct shash_alg*) ; 
 int /*<<< orphan*/  ahash_instance_headroom () ; 
 int ahash_register_instance (struct crypto_template*,struct shash_alg*) ; 
 struct shash_alg* cryptd_alloc_instance (struct crypto_alg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cryptd_check_internal (struct rtattr**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cryptd_hash_digest_enqueue ; 
 int /*<<< orphan*/  cryptd_hash_exit_tfm ; 
 int /*<<< orphan*/  cryptd_hash_export ; 
 int /*<<< orphan*/  cryptd_hash_final_enqueue ; 
 int /*<<< orphan*/  cryptd_hash_finup_enqueue ; 
 int /*<<< orphan*/  cryptd_hash_import ; 
 int /*<<< orphan*/  cryptd_hash_init_enqueue ; 
 int /*<<< orphan*/  cryptd_hash_init_tfm ; 
 int /*<<< orphan*/  cryptd_hash_setkey ; 
 int /*<<< orphan*/  cryptd_hash_update_enqueue ; 
 int /*<<< orphan*/  crypto_drop_shash (int /*<<< orphan*/ *) ; 
 int crypto_init_shash_spawn (int /*<<< orphan*/ *,struct shash_alg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 scalar_t__ crypto_shash_alg_has_setkey (struct shash_alg*) ; 
 int /*<<< orphan*/  kfree (struct shash_alg*) ; 
 struct shash_alg* shash_attr_alg (struct rtattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cryptd_create_hash(struct crypto_template *tmpl, struct rtattr **tb,
			      struct cryptd_queue *queue)
{
	struct hashd_instance_ctx *ctx;
	struct ahash_instance *inst;
	struct shash_alg *salg;
	struct crypto_alg *alg;
	u32 type = 0;
	u32 mask = 0;
	int err;

	cryptd_check_internal(tb, &type, &mask);

	salg = shash_attr_alg(tb[1], type, mask);
	if (IS_ERR(salg))
		return PTR_ERR(salg);

	alg = &salg->base;
	inst = cryptd_alloc_instance(alg, ahash_instance_headroom(),
				     sizeof(*ctx));
	err = PTR_ERR(inst);
	if (IS_ERR(inst))
		goto out_put_alg;

	ctx = ahash_instance_ctx(inst);
	ctx->queue = queue;

	err = crypto_init_shash_spawn(&ctx->spawn, salg,
				      ahash_crypto_instance(inst));
	if (err)
		goto out_free_inst;

	inst->alg.halg.base.cra_flags = CRYPTO_ALG_ASYNC |
		(alg->cra_flags & (CRYPTO_ALG_INTERNAL |
				   CRYPTO_ALG_OPTIONAL_KEY));

	inst->alg.halg.digestsize = salg->digestsize;
	inst->alg.halg.statesize = salg->statesize;
	inst->alg.halg.base.cra_ctxsize = sizeof(struct cryptd_hash_ctx);

	inst->alg.halg.base.cra_init = cryptd_hash_init_tfm;
	inst->alg.halg.base.cra_exit = cryptd_hash_exit_tfm;

	inst->alg.init   = cryptd_hash_init_enqueue;
	inst->alg.update = cryptd_hash_update_enqueue;
	inst->alg.final  = cryptd_hash_final_enqueue;
	inst->alg.finup  = cryptd_hash_finup_enqueue;
	inst->alg.export = cryptd_hash_export;
	inst->alg.import = cryptd_hash_import;
	if (crypto_shash_alg_has_setkey(salg))
		inst->alg.setkey = cryptd_hash_setkey;
	inst->alg.digest = cryptd_hash_digest_enqueue;

	err = ahash_register_instance(tmpl, inst);
	if (err) {
		crypto_drop_shash(&ctx->spawn);
out_free_inst:
		kfree(inst);
	}

out_put_alg:
	crypto_mod_put(alg);
	return err;
}