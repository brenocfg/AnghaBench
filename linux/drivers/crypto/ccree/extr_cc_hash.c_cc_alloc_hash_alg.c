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
struct device {int dummy; } ;
struct crypto_alg {int cra_ctxsize; int cra_flags; int /*<<< orphan*/  cra_init; int /*<<< orphan*/  cra_exit; scalar_t__ cra_alignmask; int /*<<< orphan*/  cra_blocksize; int /*<<< orphan*/  cra_priority; int /*<<< orphan*/  cra_module; int /*<<< orphan*/  cra_driver_name; int /*<<< orphan*/  cra_name; } ;
struct TYPE_2__ {struct crypto_alg base; } ;
struct ahash_alg {int /*<<< orphan*/ * setkey; TYPE_1__ halg; } ;
struct cc_hash_template {char* mac_name; char* mac_driver_name; char* name; char* driver_name; int /*<<< orphan*/  inter_digestsize; int /*<<< orphan*/  hw_mode; int /*<<< orphan*/  hash_mode; int /*<<< orphan*/  blocksize; struct ahash_alg template_ahash; } ;
struct cc_hash_ctx {int dummy; } ;
struct cc_hash_alg {int /*<<< orphan*/  inter_digestsize; int /*<<< orphan*/  hw_mode; int /*<<< orphan*/  hash_mode; struct ahash_alg ahash_alg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_CRA_PRIO ; 
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_KERN_DRIVER_ONLY ; 
 int /*<<< orphan*/  CRYPTO_MAX_ALG_NAME ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct cc_hash_alg* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  cc_cra_exit ; 
 int /*<<< orphan*/  cc_cra_init ; 
 struct cc_hash_alg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static struct cc_hash_alg *cc_alloc_hash_alg(struct cc_hash_template *template,
					     struct device *dev, bool keyed)
{
	struct cc_hash_alg *t_crypto_alg;
	struct crypto_alg *alg;
	struct ahash_alg *halg;

	t_crypto_alg = kzalloc(sizeof(*t_crypto_alg), GFP_KERNEL);
	if (!t_crypto_alg)
		return ERR_PTR(-ENOMEM);

	t_crypto_alg->ahash_alg = template->template_ahash;
	halg = &t_crypto_alg->ahash_alg;
	alg = &halg->halg.base;

	if (keyed) {
		snprintf(alg->cra_name, CRYPTO_MAX_ALG_NAME, "%s",
			 template->mac_name);
		snprintf(alg->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
			 template->mac_driver_name);
	} else {
		halg->setkey = NULL;
		snprintf(alg->cra_name, CRYPTO_MAX_ALG_NAME, "%s",
			 template->name);
		snprintf(alg->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
			 template->driver_name);
	}
	alg->cra_module = THIS_MODULE;
	alg->cra_ctxsize = sizeof(struct cc_hash_ctx);
	alg->cra_priority = CC_CRA_PRIO;
	alg->cra_blocksize = template->blocksize;
	alg->cra_alignmask = 0;
	alg->cra_exit = cc_cra_exit;

	alg->cra_init = cc_cra_init;
	alg->cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_KERN_DRIVER_ONLY;

	t_crypto_alg->hash_mode = template->hash_mode;
	t_crypto_alg->hw_mode = template->hw_mode;
	t_crypto_alg->inter_digestsize = template->inter_digestsize;

	return t_crypto_alg;
}