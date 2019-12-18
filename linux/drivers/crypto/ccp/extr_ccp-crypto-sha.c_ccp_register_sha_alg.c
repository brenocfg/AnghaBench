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
struct list_head {int dummy; } ;
struct crypto_alg {int cra_flags; int cra_ctxsize; int /*<<< orphan*/  cra_name; int /*<<< orphan*/  cra_module; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; int /*<<< orphan*/  cra_priority; int /*<<< orphan*/  cra_blocksize; int /*<<< orphan*/  cra_driver_name; } ;
struct hash_alg_common {int statesize; struct crypto_alg base; int /*<<< orphan*/  digestsize; } ;
struct ccp_sha_exp_ctx {int dummy; } ;
struct ccp_sha_def {char* name; char* drv_name; int /*<<< orphan*/  block_size; int /*<<< orphan*/  digest_size; int /*<<< orphan*/  type; } ;
struct ccp_ctx {int dummy; } ;
struct ahash_alg {struct hash_alg_common halg; int /*<<< orphan*/  import; int /*<<< orphan*/  export; int /*<<< orphan*/  digest; int /*<<< orphan*/  finup; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  init; } ;
struct ccp_crypto_ahash_alg {int /*<<< orphan*/  entry; struct ahash_alg alg; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCP_CRA_PRIORITY ; 
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_KERN_DRIVER_ONLY ; 
 int CRYPTO_ALG_NEED_FALLBACK ; 
 int /*<<< orphan*/  CRYPTO_MAX_ALG_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int ccp_register_hmac_alg (struct list_head*,struct ccp_sha_def const*,struct ccp_crypto_ahash_alg*) ; 
 int /*<<< orphan*/  ccp_sha_cra_exit ; 
 int /*<<< orphan*/  ccp_sha_cra_init ; 
 int /*<<< orphan*/  ccp_sha_digest ; 
 int /*<<< orphan*/  ccp_sha_export ; 
 int /*<<< orphan*/  ccp_sha_final ; 
 int /*<<< orphan*/  ccp_sha_finup ; 
 int /*<<< orphan*/  ccp_sha_import ; 
 int /*<<< orphan*/  ccp_sha_init ; 
 int /*<<< orphan*/  ccp_sha_update ; 
 int crypto_register_ahash (struct ahash_alg*) ; 
 int /*<<< orphan*/  kfree (struct ccp_crypto_ahash_alg*) ; 
 struct ccp_crypto_ahash_alg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int ccp_register_sha_alg(struct list_head *head,
				const struct ccp_sha_def *def)
{
	struct ccp_crypto_ahash_alg *ccp_alg;
	struct ahash_alg *alg;
	struct hash_alg_common *halg;
	struct crypto_alg *base;
	int ret;

	ccp_alg = kzalloc(sizeof(*ccp_alg), GFP_KERNEL);
	if (!ccp_alg)
		return -ENOMEM;

	INIT_LIST_HEAD(&ccp_alg->entry);

	ccp_alg->type = def->type;

	alg = &ccp_alg->alg;
	alg->init = ccp_sha_init;
	alg->update = ccp_sha_update;
	alg->final = ccp_sha_final;
	alg->finup = ccp_sha_finup;
	alg->digest = ccp_sha_digest;
	alg->export = ccp_sha_export;
	alg->import = ccp_sha_import;

	halg = &alg->halg;
	halg->digestsize = def->digest_size;
	halg->statesize = sizeof(struct ccp_sha_exp_ctx);

	base = &halg->base;
	snprintf(base->cra_name, CRYPTO_MAX_ALG_NAME, "%s", def->name);
	snprintf(base->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		 def->drv_name);
	base->cra_flags = CRYPTO_ALG_ASYNC |
			  CRYPTO_ALG_KERN_DRIVER_ONLY |
			  CRYPTO_ALG_NEED_FALLBACK;
	base->cra_blocksize = def->block_size;
	base->cra_ctxsize = sizeof(struct ccp_ctx);
	base->cra_priority = CCP_CRA_PRIORITY;
	base->cra_init = ccp_sha_cra_init;
	base->cra_exit = ccp_sha_cra_exit;
	base->cra_module = THIS_MODULE;

	ret = crypto_register_ahash(alg);
	if (ret) {
		pr_err("%s ahash algorithm registration error (%d)\n",
		       base->cra_name, ret);
		kfree(ccp_alg);
		return ret;
	}

	list_add(&ccp_alg->entry, head);

	ret = ccp_register_hmac_alg(head, def, ccp_alg);

	return ret;
}