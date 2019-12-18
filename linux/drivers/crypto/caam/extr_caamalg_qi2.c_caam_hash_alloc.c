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
struct crypto_alg {int cra_ctxsize; int /*<<< orphan*/  cra_flags; scalar_t__ cra_alignmask; int /*<<< orphan*/  cra_blocksize; int /*<<< orphan*/  cra_priority; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; int /*<<< orphan*/  cra_module; int /*<<< orphan*/  cra_driver_name; int /*<<< orphan*/  cra_name; } ;
struct TYPE_2__ {struct crypto_alg base; } ;
struct ahash_alg {int /*<<< orphan*/ * setkey; TYPE_1__ halg; } ;
struct caam_hash_template {char* hmac_name; char* hmac_driver_name; char* name; char* driver_name; int /*<<< orphan*/  alg_type; int /*<<< orphan*/  blocksize; struct ahash_alg template_ahash; } ;
struct caam_hash_ctx {int dummy; } ;
struct caam_hash_alg {struct device* dev; int /*<<< orphan*/  alg_type; struct ahash_alg ahash_alg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAAM_CRA_PRIORITY ; 
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int /*<<< orphan*/  CRYPTO_MAX_ALG_NAME ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct caam_hash_alg* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  caam_hash_cra_exit ; 
 int /*<<< orphan*/  caam_hash_cra_init ; 
 struct caam_hash_alg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static struct caam_hash_alg *caam_hash_alloc(struct device *dev,
	struct caam_hash_template *template, bool keyed)
{
	struct caam_hash_alg *t_alg;
	struct ahash_alg *halg;
	struct crypto_alg *alg;

	t_alg = kzalloc(sizeof(*t_alg), GFP_KERNEL);
	if (!t_alg)
		return ERR_PTR(-ENOMEM);

	t_alg->ahash_alg = template->template_ahash;
	halg = &t_alg->ahash_alg;
	alg = &halg->halg.base;

	if (keyed) {
		snprintf(alg->cra_name, CRYPTO_MAX_ALG_NAME, "%s",
			 template->hmac_name);
		snprintf(alg->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
			 template->hmac_driver_name);
	} else {
		snprintf(alg->cra_name, CRYPTO_MAX_ALG_NAME, "%s",
			 template->name);
		snprintf(alg->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
			 template->driver_name);
		t_alg->ahash_alg.setkey = NULL;
	}
	alg->cra_module = THIS_MODULE;
	alg->cra_init = caam_hash_cra_init;
	alg->cra_exit = caam_hash_cra_exit;
	alg->cra_ctxsize = sizeof(struct caam_hash_ctx);
	alg->cra_priority = CAAM_CRA_PRIORITY;
	alg->cra_blocksize = template->blocksize;
	alg->cra_alignmask = 0;
	alg->cra_flags = CRYPTO_ALG_ASYNC;

	t_alg->alg_type = template->alg_type;
	t_alg->dev = dev;

	return t_alg;
}