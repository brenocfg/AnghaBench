#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iproc_ctx_s {int dummy; } ;
struct TYPE_4__ {int cra_ctxsize; int /*<<< orphan*/  cra_driver_name; int /*<<< orphan*/  cra_flags; scalar_t__ cra_alignmask; int /*<<< orphan*/  cra_priority; int /*<<< orphan*/  cra_module; } ;
struct aead_alg {TYPE_2__ base; int /*<<< orphan*/  exit; int /*<<< orphan*/  init; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setauthsize; } ;
struct TYPE_3__ {struct aead_alg aead; } ;
struct iproc_alg_s {int registered; TYPE_1__ alg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  aead_cra_exit ; 
 int /*<<< orphan*/  aead_cra_init ; 
 int /*<<< orphan*/  aead_decrypt ; 
 int /*<<< orphan*/  aead_encrypt ; 
 int /*<<< orphan*/  aead_pri ; 
 int /*<<< orphan*/  aead_setauthsize ; 
 int crypto_register_aead (struct aead_alg*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spu_register_aead(struct iproc_alg_s *driver_alg)
{
	struct aead_alg *aead = &driver_alg->alg.aead;
	int err;

	aead->base.cra_module = THIS_MODULE;
	aead->base.cra_priority = aead_pri;
	aead->base.cra_alignmask = 0;
	aead->base.cra_ctxsize = sizeof(struct iproc_ctx_s);

	aead->base.cra_flags |= CRYPTO_ALG_ASYNC;
	/* setkey set in alg initialization */
	aead->setauthsize = aead_setauthsize;
	aead->encrypt = aead_encrypt;
	aead->decrypt = aead_decrypt;
	aead->init = aead_cra_init;
	aead->exit = aead_cra_exit;

	err = crypto_register_aead(aead);
	/* Mark alg as having been registered, if successful */
	if (err == 0)
		driver_alg->registered = true;
	pr_debug("  registered aead %s\n", aead->base.cra_driver_name);
	return err;
}