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
struct TYPE_5__ {char* cra_name; char* cra_driver_name; int cra_priority; int cra_alignmask; } ;
struct hash_alg_common {int digestsize; TYPE_1__ base; } ;
struct crypto_template {int dummy; } ;
struct crypto_ccm_ctx {int dummy; } ;
struct crypto_attr_type {int type; int mask; } ;
struct crypto_alg {int type; int mask; } ;
struct ccm_instance_ctx {int /*<<< orphan*/  mac; int /*<<< orphan*/  ctr; } ;
struct TYPE_7__ {int cra_flags; int cra_priority; int cra_blocksize; int cra_alignmask; int cra_ctxsize; int /*<<< orphan*/  cra_driver_name; int /*<<< orphan*/  cra_name; } ;
struct TYPE_8__ {int ivsize; int maxauthsize; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setauthsize; int /*<<< orphan*/  setkey; int /*<<< orphan*/  exit; int /*<<< orphan*/  init; TYPE_3__ base; int /*<<< orphan*/  chunksize; } ;
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
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_attr_type*) ; 
 int PTR_ERR (struct crypto_attr_type*) ; 
 struct hash_alg_common* __crypto_hash_alg_common (struct crypto_attr_type*) ; 
 int /*<<< orphan*/  aead_crypto_instance (struct aead_instance*) ; 
 struct ccm_instance_ctx* aead_instance_ctx (struct aead_instance*) ; 
 int aead_register_instance (struct crypto_template*,struct aead_instance*) ; 
 int /*<<< orphan*/  crypto_ahash_type ; 
 int /*<<< orphan*/  crypto_ccm_decrypt ; 
 int /*<<< orphan*/  crypto_ccm_encrypt ; 
 int /*<<< orphan*/  crypto_ccm_exit_tfm ; 
 int /*<<< orphan*/  crypto_ccm_free ; 
 int /*<<< orphan*/  crypto_ccm_init_tfm ; 
 int /*<<< orphan*/  crypto_ccm_setauthsize ; 
 int /*<<< orphan*/  crypto_ccm_setkey ; 
 int /*<<< orphan*/  crypto_drop_ahash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_drop_skcipher (int /*<<< orphan*/ *) ; 
 struct crypto_attr_type* crypto_find_alg (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct crypto_attr_type* crypto_get_attr_type (struct rtattr**) ; 
 int crypto_grab_skcipher (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_init_ahash_spawn (int /*<<< orphan*/ *,struct hash_alg_common*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_attr_type*) ; 
 int /*<<< orphan*/  crypto_requires_sync (int,int) ; 
 int /*<<< orphan*/  crypto_set_skcipher_spawn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_alg_chunksize (struct skcipher_alg*) ; 
 int crypto_skcipher_alg_ivsize (struct skcipher_alg*) ; 
 struct skcipher_alg* crypto_spawn_skcipher_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct aead_instance*) ; 
 struct aead_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ snprintf (int /*<<< orphan*/ ,scalar_t__,char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int crypto_ccm_create_common(struct crypto_template *tmpl,
				    struct rtattr **tb,
				    const char *ctr_name,
				    const char *mac_name)
{
	struct crypto_attr_type *algt;
	struct aead_instance *inst;
	struct skcipher_alg *ctr;
	struct crypto_alg *mac_alg;
	struct hash_alg_common *mac;
	struct ccm_instance_ctx *ictx;
	int err;

	algt = crypto_get_attr_type(tb);
	if (IS_ERR(algt))
		return PTR_ERR(algt);

	if ((algt->type ^ CRYPTO_ALG_TYPE_AEAD) & algt->mask)
		return -EINVAL;

	mac_alg = crypto_find_alg(mac_name, &crypto_ahash_type,
				  CRYPTO_ALG_TYPE_HASH,
				  CRYPTO_ALG_TYPE_AHASH_MASK |
				  CRYPTO_ALG_ASYNC);
	if (IS_ERR(mac_alg))
		return PTR_ERR(mac_alg);

	mac = __crypto_hash_alg_common(mac_alg);
	err = -EINVAL;
	if (strncmp(mac->base.cra_name, "cbcmac(", 7) != 0 ||
	    mac->digestsize != 16)
		goto out_put_mac;

	inst = kzalloc(sizeof(*inst) + sizeof(*ictx), GFP_KERNEL);
	err = -ENOMEM;
	if (!inst)
		goto out_put_mac;

	ictx = aead_instance_ctx(inst);
	err = crypto_init_ahash_spawn(&ictx->mac, mac,
				      aead_crypto_instance(inst));
	if (err)
		goto err_free_inst;

	crypto_set_skcipher_spawn(&ictx->ctr, aead_crypto_instance(inst));
	err = crypto_grab_skcipher(&ictx->ctr, ctr_name, 0,
				   crypto_requires_sync(algt->type,
							algt->mask));
	if (err)
		goto err_drop_mac;

	ctr = crypto_spawn_skcipher_alg(&ictx->ctr);

	/* The skcipher algorithm must be CTR mode, using 16-byte blocks. */
	err = -EINVAL;
	if (strncmp(ctr->base.cra_name, "ctr(", 4) != 0 ||
	    crypto_skcipher_alg_ivsize(ctr) != 16 ||
	    ctr->base.cra_blocksize != 1)
		goto err_drop_ctr;

	/* ctr and cbcmac must use the same underlying block cipher. */
	if (strcmp(ctr->base.cra_name + 4, mac->base.cra_name + 7) != 0)
		goto err_drop_ctr;

	err = -ENAMETOOLONG;
	if (snprintf(inst->alg.base.cra_name, CRYPTO_MAX_ALG_NAME,
		     "ccm(%s", ctr->base.cra_name + 4) >= CRYPTO_MAX_ALG_NAME)
		goto err_drop_ctr;

	if (snprintf(inst->alg.base.cra_driver_name, CRYPTO_MAX_ALG_NAME,
		     "ccm_base(%s,%s)", ctr->base.cra_driver_name,
		     mac->base.cra_driver_name) >= CRYPTO_MAX_ALG_NAME)
		goto err_drop_ctr;

	inst->alg.base.cra_flags = ctr->base.cra_flags & CRYPTO_ALG_ASYNC;
	inst->alg.base.cra_priority = (mac->base.cra_priority +
				       ctr->base.cra_priority) / 2;
	inst->alg.base.cra_blocksize = 1;
	inst->alg.base.cra_alignmask = mac->base.cra_alignmask |
				       ctr->base.cra_alignmask;
	inst->alg.ivsize = 16;
	inst->alg.chunksize = crypto_skcipher_alg_chunksize(ctr);
	inst->alg.maxauthsize = 16;
	inst->alg.base.cra_ctxsize = sizeof(struct crypto_ccm_ctx);
	inst->alg.init = crypto_ccm_init_tfm;
	inst->alg.exit = crypto_ccm_exit_tfm;
	inst->alg.setkey = crypto_ccm_setkey;
	inst->alg.setauthsize = crypto_ccm_setauthsize;
	inst->alg.encrypt = crypto_ccm_encrypt;
	inst->alg.decrypt = crypto_ccm_decrypt;

	inst->free = crypto_ccm_free;

	err = aead_register_instance(tmpl, inst);
	if (err)
		goto err_drop_ctr;

out_put_mac:
	crypto_mod_put(mac_alg);
	return err;

err_drop_ctr:
	crypto_drop_skcipher(&ictx->ctr);
err_drop_mac:
	crypto_drop_ahash(&ictx->mac);
err_free_inst:
	kfree(inst);
	goto out_put_mac;
}