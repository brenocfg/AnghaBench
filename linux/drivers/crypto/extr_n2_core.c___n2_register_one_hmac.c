#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct n2_hmac_ctx {int dummy; } ;
struct crypto_alg {int cra_ctxsize; int /*<<< orphan*/  cra_name; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; int /*<<< orphan*/  cra_driver_name; } ;
struct TYPE_9__ {struct crypto_alg base; } ;
struct ahash_alg {TYPE_4__ halg; int /*<<< orphan*/  setkey; int /*<<< orphan*/  digest; } ;
struct TYPE_10__ {int /*<<< orphan*/  entry; struct ahash_alg alg; } ;
struct n2_hmac_alg {char* child_alg; TYPE_5__ derived; } ;
struct TYPE_6__ {char* cra_name; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
struct TYPE_8__ {TYPE_2__ halg; } ;
struct n2_ahash_alg {TYPE_3__ alg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_MAX_ALG_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int crypto_register_ahash (struct ahash_alg*) ; 
 int /*<<< orphan*/  hmac_algs ; 
 int /*<<< orphan*/  kfree (struct n2_hmac_alg*) ; 
 struct n2_hmac_alg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,struct n2_ahash_alg*,int) ; 
 int /*<<< orphan*/  n2_hmac_async_digest ; 
 int /*<<< orphan*/  n2_hmac_async_setkey ; 
 int /*<<< orphan*/  n2_hmac_cra_exit ; 
 int /*<<< orphan*/  n2_hmac_cra_init ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int __n2_register_one_hmac(struct n2_ahash_alg *n2ahash)
{
	struct n2_hmac_alg *p = kzalloc(sizeof(*p), GFP_KERNEL);
	struct ahash_alg *ahash;
	struct crypto_alg *base;
	int err;

	if (!p)
		return -ENOMEM;

	p->child_alg = n2ahash->alg.halg.base.cra_name;
	memcpy(&p->derived, n2ahash, sizeof(struct n2_ahash_alg));
	INIT_LIST_HEAD(&p->derived.entry);

	ahash = &p->derived.alg;
	ahash->digest = n2_hmac_async_digest;
	ahash->setkey = n2_hmac_async_setkey;

	base = &ahash->halg.base;
	snprintf(base->cra_name, CRYPTO_MAX_ALG_NAME, "hmac(%s)", p->child_alg);
	snprintf(base->cra_driver_name, CRYPTO_MAX_ALG_NAME, "hmac-%s-n2", p->child_alg);

	base->cra_ctxsize = sizeof(struct n2_hmac_ctx);
	base->cra_init = n2_hmac_cra_init;
	base->cra_exit = n2_hmac_cra_exit;

	list_add(&p->derived.entry, &hmac_algs);
	err = crypto_register_ahash(ahash);
	if (err) {
		pr_err("%s alg registration failed\n", base->cra_name);
		list_del(&p->derived.entry);
		kfree(p);
	} else {
		pr_info("%s alg registered\n", base->cra_name);
	}
	return err;
}