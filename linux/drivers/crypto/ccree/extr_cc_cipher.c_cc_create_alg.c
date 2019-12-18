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
struct TYPE_2__ {int cra_ctxsize; int cra_flags; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; scalar_t__ cra_alignmask; int /*<<< orphan*/  cra_blocksize; int /*<<< orphan*/  cra_priority; int /*<<< orphan*/  cra_module; int /*<<< orphan*/  cra_driver_name; int /*<<< orphan*/  cra_name; } ;
struct skcipher_alg {TYPE_1__ base; } ;
struct device {int dummy; } ;
struct cc_crypto_alg {int /*<<< orphan*/  data_unit; int /*<<< orphan*/  flow_mode; int /*<<< orphan*/  cipher_mode; struct skcipher_alg skcipher_alg; } ;
struct cc_cipher_ctx {int dummy; } ;
struct cc_alg_template {char* name; char* driver_name; int /*<<< orphan*/  data_unit; int /*<<< orphan*/  flow_mode; int /*<<< orphan*/  cipher_mode; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  template_skcipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_CRA_PRIO ; 
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_KERN_DRIVER_ONLY ; 
 int /*<<< orphan*/  CRYPTO_MAX_ALG_NAME ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct cc_crypto_alg* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  cc_cipher_exit ; 
 int /*<<< orphan*/  cc_cipher_init ; 
 struct cc_crypto_alg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct skcipher_alg*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static struct cc_crypto_alg *cc_create_alg(const struct cc_alg_template *tmpl,
					   struct device *dev)
{
	struct cc_crypto_alg *t_alg;
	struct skcipher_alg *alg;

	t_alg = kzalloc(sizeof(*t_alg), GFP_KERNEL);
	if (!t_alg)
		return ERR_PTR(-ENOMEM);

	alg = &t_alg->skcipher_alg;

	memcpy(alg, &tmpl->template_skcipher, sizeof(*alg));

	snprintf(alg->base.cra_name, CRYPTO_MAX_ALG_NAME, "%s", tmpl->name);
	snprintf(alg->base.cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		 tmpl->driver_name);
	alg->base.cra_module = THIS_MODULE;
	alg->base.cra_priority = CC_CRA_PRIO;
	alg->base.cra_blocksize = tmpl->blocksize;
	alg->base.cra_alignmask = 0;
	alg->base.cra_ctxsize = sizeof(struct cc_cipher_ctx);

	alg->base.cra_init = cc_cipher_init;
	alg->base.cra_exit = cc_cipher_exit;
	alg->base.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_KERN_DRIVER_ONLY;

	t_alg->cipher_mode = tmpl->cipher_mode;
	t_alg->flow_mode = tmpl->flow_mode;
	t_alg->data_unit = tmpl->data_unit;

	return t_alg;
}