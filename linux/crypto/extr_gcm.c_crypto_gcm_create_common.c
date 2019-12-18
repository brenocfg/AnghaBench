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
struct TYPE_6__ {char* cra_name; int cra_blocksize; char* cra_driver_name; int cra_flags; int cra_priority; int cra_alignmask; } ;
struct skcipher_alg {TYPE_2__ base; } ;
struct rtattr {int dummy; } ;
struct TYPE_5__ {int cra_flags; int cra_priority; int cra_alignmask; int /*<<< orphan*/  cra_name; } ;
struct hash_alg_common {int digestsize; TYPE_1__ base; } ;
struct gcm_instance_ctx {int /*<<< orphan*/  ghash; int /*<<< orphan*/  ctr; } ;
struct crypto_template {int dummy; } ;
struct crypto_gcm_ctx {int dummy; } ;
struct crypto_attr_type {int type; int mask; char* cra_driver_name; } ;
struct crypto_alg {int type; int mask; char* cra_driver_name; } ;
struct TYPE_7__ {int cra_flags; int cra_priority; int cra_blocksize; int cra_alignmask; int cra_ctxsize; int /*<<< orphan*/  cra_driver_name; int /*<<< orphan*/  cra_name; } ;
struct TYPE_8__ {int maxauthsize; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setauthsize; int /*<<< orphan*/  setkey; int /*<<< orphan*/  exit; int /*<<< orphan*/  init; int /*<<< orphan*/  chunksize; int /*<<< orphan*/  ivsize; TYPE_3__ base; } ;
struct aead_instance {int /*<<< orphan*/  free; TYPE_4__ alg; } ;

/* Variables and functions */
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_TYPE_AEAD ; 
 int CRYPTO_ALG_TYPE_AHASH_MASK ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_HASH ; 
 scalar_t__ CRYPTO_MAX_ALG_NAME ; 
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GCM_AES_IV_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_attr_type*) ; 
 int PTR_ERR (struct crypto_attr_type*) ; 
 struct hash_alg_common* __crypto_hash_alg_common (struct crypto_attr_type*) ; 
 int /*<<< orphan*/  aead_crypto_instance (struct aead_instance*) ; 
 struct gcm_instance_ctx* aead_instance_ctx (struct aead_instance*) ; 
 int aead_register_instance (struct crypto_template*,struct aead_instance*) ; 
 int /*<<< orphan*/  crypto_ahash_type ; 
 int /*<<< orphan*/  crypto_drop_ahash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_drop_skcipher (int /*<<< orphan*/ *) ; 
 struct crypto_attr_type* crypto_find_alg (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crypto_gcm_decrypt ; 
 int /*<<< orphan*/  crypto_gcm_encrypt ; 
 int /*<<< orphan*/  crypto_gcm_exit_tfm ; 
 int /*<<< orphan*/  crypto_gcm_free ; 
 int /*<<< orphan*/  crypto_gcm_init_tfm ; 
 int /*<<< orphan*/  crypto_gcm_setauthsize ; 
 int /*<<< orphan*/  crypto_gcm_setkey ; 
 struct crypto_attr_type* crypto_get_attr_type (struct rtattr**) ; 
 int crypto_grab_skcipher (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 int crypto_init_ahash_spawn (int /*<<< orphan*/ *,struct hash_alg_common*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_attr_type*) ; 
 int crypto_requires_sync (int,int) ; 
 int /*<<< orphan*/  crypto_set_skcipher_spawn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_alg_chunksize (struct skcipher_alg*) ; 
 int crypto_skcipher_alg_ivsize (struct skcipher_alg*) ; 
 struct skcipher_alg* crypto_spawn_skcipher_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct aead_instance*) ; 
 struct aead_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ snprintf (int /*<<< orphan*/ ,scalar_t__,char*,char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int crypto_gcm_create_common(struct crypto_template *tmpl,
				    struct rtattr **tb,
				    const char *ctr_name,
				    const char *ghash_name)
{
	struct crypto_attr_type *algt;
	struct aead_instance *inst;
	struct skcipher_alg *ctr;
	struct crypto_alg *ghash_alg;
	struct hash_alg_common *ghash;
	struct gcm_instance_ctx *ctx;
	int err;

	algt = crypto_get_attr_type(tb);
	if (IS_ERR(algt))
		return PTR_ERR(algt);

	if ((algt->type ^ CRYPTO_ALG_TYPE_AEAD) & algt->mask)
		return -EINVAL;

	ghash_alg = crypto_find_alg(ghash_name, &crypto_ahash_type,
				    CRYPTO_ALG_TYPE_HASH,
				    CRYPTO_ALG_TYPE_AHASH_MASK |
				    crypto_requires_sync(algt->type,
							 algt->mask));
	if (IS_ERR(ghash_alg))
		return PTR_ERR(ghash_alg);

	ghash = __crypto_hash_alg_common(ghash_alg);

	err = -ENOMEM;
	inst = kzalloc(sizeof(*inst) + sizeof(*ctx), GFP_KERNEL);
	if (!inst)
		goto out_put_ghash;

	ctx = aead_instance_ctx(inst);
	err = crypto_init_ahash_spawn(&ctx->ghash, ghash,
				      aead_crypto_instance(inst));
	if (err)
		goto err_free_inst;

	err = -EINVAL;
	if (strcmp(ghash->base.cra_name, "ghash") != 0 ||
	    ghash->digestsize != 16)
		goto err_drop_ghash;

	crypto_set_skcipher_spawn(&ctx->ctr, aead_crypto_instance(inst));
	err = crypto_grab_skcipher(&ctx->ctr, ctr_name, 0,
				   crypto_requires_sync(algt->type,
							algt->mask));
	if (err)
		goto err_drop_ghash;

	ctr = crypto_spawn_skcipher_alg(&ctx->ctr);

	/* The skcipher algorithm must be CTR mode, using 16-byte blocks. */
	err = -EINVAL;
	if (strncmp(ctr->base.cra_name, "ctr(", 4) != 0 ||
	    crypto_skcipher_alg_ivsize(ctr) != 16 ||
	    ctr->base.cra_blocksize != 1)
		goto out_put_ctr;

	err = -ENAMETOOLONG;
	if (snprintf(inst->alg.base.cra_name, CRYPTO_MAX_ALG_NAME,
		     "gcm(%s", ctr->base.cra_name + 4) >= CRYPTO_MAX_ALG_NAME)
		goto out_put_ctr;

	if (snprintf(inst->alg.base.cra_driver_name, CRYPTO_MAX_ALG_NAME,
		     "gcm_base(%s,%s)", ctr->base.cra_driver_name,
		     ghash_alg->cra_driver_name) >=
	    CRYPTO_MAX_ALG_NAME)
		goto out_put_ctr;

	inst->alg.base.cra_flags = (ghash->base.cra_flags |
				    ctr->base.cra_flags) & CRYPTO_ALG_ASYNC;
	inst->alg.base.cra_priority = (ghash->base.cra_priority +
				       ctr->base.cra_priority) / 2;
	inst->alg.base.cra_blocksize = 1;
	inst->alg.base.cra_alignmask = ghash->base.cra_alignmask |
				       ctr->base.cra_alignmask;
	inst->alg.base.cra_ctxsize = sizeof(struct crypto_gcm_ctx);
	inst->alg.ivsize = GCM_AES_IV_SIZE;
	inst->alg.chunksize = crypto_skcipher_alg_chunksize(ctr);
	inst->alg.maxauthsize = 16;
	inst->alg.init = crypto_gcm_init_tfm;
	inst->alg.exit = crypto_gcm_exit_tfm;
	inst->alg.setkey = crypto_gcm_setkey;
	inst->alg.setauthsize = crypto_gcm_setauthsize;
	inst->alg.encrypt = crypto_gcm_encrypt;
	inst->alg.decrypt = crypto_gcm_decrypt;

	inst->free = crypto_gcm_free;

	err = aead_register_instance(tmpl, inst);
	if (err)
		goto out_put_ctr;

out_put_ghash:
	crypto_mod_put(ghash_alg);
	return err;

out_put_ctr:
	crypto_drop_skcipher(&ctx->ctr);
err_drop_ghash:
	crypto_drop_ahash(&ctx->ghash);
err_free_inst:
	kfree(inst);
	goto out_put_ghash;
}