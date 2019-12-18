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
struct list_head {int dummy; } ;
struct ccp_rsa_def {char* name; char* driver_name; struct akcipher_alg* alg_defaults; } ;
struct TYPE_2__ {int /*<<< orphan*/  cra_name; int /*<<< orphan*/  cra_driver_name; } ;
struct akcipher_alg {TYPE_1__ base; } ;
struct ccp_crypto_akcipher_alg {int /*<<< orphan*/  entry; struct akcipher_alg alg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_MAX_ALG_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int crypto_register_akcipher (struct akcipher_alg*) ; 
 int /*<<< orphan*/  kfree (struct ccp_crypto_akcipher_alg*) ; 
 struct ccp_crypto_akcipher_alg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int ccp_register_rsa_alg(struct list_head *head,
			        const struct ccp_rsa_def *def)
{
	struct ccp_crypto_akcipher_alg *ccp_alg;
	struct akcipher_alg *alg;
	int ret;

	ccp_alg = kzalloc(sizeof(*ccp_alg), GFP_KERNEL);
	if (!ccp_alg)
		return -ENOMEM;

	INIT_LIST_HEAD(&ccp_alg->entry);

	alg = &ccp_alg->alg;
	*alg = *def->alg_defaults;
	snprintf(alg->base.cra_name, CRYPTO_MAX_ALG_NAME, "%s", def->name);
	snprintf(alg->base.cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		 def->driver_name);
	ret = crypto_register_akcipher(alg);
	if (ret) {
		pr_err("%s akcipher algorithm registration error (%d)\n",
		       alg->base.cra_name, ret);
		kfree(ccp_alg);
		return ret;
	}

	list_add(&ccp_alg->entry, head);

	return 0;
}