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
struct n2_hash_tmpl {scalar_t__ hmac_type; char* name; int /*<<< orphan*/  block_size; int /*<<< orphan*/  digest_size; int /*<<< orphan*/  hw_op_hashsz; int /*<<< orphan*/  auth_type; int /*<<< orphan*/  hash_init; int /*<<< orphan*/  hash_zero; } ;
struct n2_hash_ctx {int dummy; } ;
struct crypto_alg {int cra_flags; int cra_ctxsize; int /*<<< orphan*/  cra_name; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; int /*<<< orphan*/  cra_module; int /*<<< orphan*/  cra_blocksize; int /*<<< orphan*/  cra_priority; int /*<<< orphan*/  cra_driver_name; } ;
struct hash_alg_common {struct crypto_alg base; int /*<<< orphan*/  digestsize; } ;
struct ahash_alg {struct hash_alg_common halg; int /*<<< orphan*/  import; int /*<<< orphan*/  export; int /*<<< orphan*/  digest; int /*<<< orphan*/  finup; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  init; } ;
struct n2_ahash_alg {scalar_t__ hmac_type; int /*<<< orphan*/  entry; struct ahash_alg alg; int /*<<< orphan*/  digest_size; int /*<<< orphan*/  hw_op_hashsz; int /*<<< orphan*/  auth_type; int /*<<< orphan*/  hash_init; int /*<<< orphan*/  hash_zero; } ;

/* Variables and functions */
 scalar_t__ AUTH_TYPE_RESERVED ; 
 int CRYPTO_ALG_KERN_DRIVER_ONLY ; 
 int CRYPTO_ALG_NEED_FALLBACK ; 
 int /*<<< orphan*/  CRYPTO_MAX_ALG_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  N2_CRA_PRIORITY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int __n2_register_one_hmac (struct n2_ahash_alg*) ; 
 int /*<<< orphan*/  ahash_algs ; 
 int crypto_register_ahash (struct ahash_alg*) ; 
 int /*<<< orphan*/  kfree (struct n2_ahash_alg*) ; 
 struct n2_ahash_alg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n2_hash_async_digest ; 
 int /*<<< orphan*/  n2_hash_async_final ; 
 int /*<<< orphan*/  n2_hash_async_finup ; 
 int /*<<< orphan*/  n2_hash_async_init ; 
 int /*<<< orphan*/  n2_hash_async_noexport ; 
 int /*<<< orphan*/  n2_hash_async_noimport ; 
 int /*<<< orphan*/  n2_hash_async_update ; 
 int /*<<< orphan*/  n2_hash_cra_exit ; 
 int /*<<< orphan*/  n2_hash_cra_init ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int __n2_register_one_ahash(const struct n2_hash_tmpl *tmpl)
{
	struct n2_ahash_alg *p = kzalloc(sizeof(*p), GFP_KERNEL);
	struct hash_alg_common *halg;
	struct crypto_alg *base;
	struct ahash_alg *ahash;
	int err;

	if (!p)
		return -ENOMEM;

	p->hash_zero = tmpl->hash_zero;
	p->hash_init = tmpl->hash_init;
	p->auth_type = tmpl->auth_type;
	p->hmac_type = tmpl->hmac_type;
	p->hw_op_hashsz = tmpl->hw_op_hashsz;
	p->digest_size = tmpl->digest_size;

	ahash = &p->alg;
	ahash->init = n2_hash_async_init;
	ahash->update = n2_hash_async_update;
	ahash->final = n2_hash_async_final;
	ahash->finup = n2_hash_async_finup;
	ahash->digest = n2_hash_async_digest;
	ahash->export = n2_hash_async_noexport;
	ahash->import = n2_hash_async_noimport;

	halg = &ahash->halg;
	halg->digestsize = tmpl->digest_size;

	base = &halg->base;
	snprintf(base->cra_name, CRYPTO_MAX_ALG_NAME, "%s", tmpl->name);
	snprintf(base->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s-n2", tmpl->name);
	base->cra_priority = N2_CRA_PRIORITY;
	base->cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY |
			  CRYPTO_ALG_NEED_FALLBACK;
	base->cra_blocksize = tmpl->block_size;
	base->cra_ctxsize = sizeof(struct n2_hash_ctx);
	base->cra_module = THIS_MODULE;
	base->cra_init = n2_hash_cra_init;
	base->cra_exit = n2_hash_cra_exit;

	list_add(&p->entry, &ahash_algs);
	err = crypto_register_ahash(ahash);
	if (err) {
		pr_err("%s alg registration failed\n", base->cra_name);
		list_del(&p->entry);
		kfree(p);
	} else {
		pr_info("%s alg registered\n", base->cra_name);
	}
	if (!err && p->hmac_type != AUTH_TYPE_RESERVED)
		err = __n2_register_one_hmac(p);
	return err;
}