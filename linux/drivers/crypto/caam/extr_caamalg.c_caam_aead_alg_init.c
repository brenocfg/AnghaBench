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
struct caam_ctx {int dummy; } ;
struct TYPE_2__ {int cra_ctxsize; int cra_flags; int /*<<< orphan*/  cra_priority; int /*<<< orphan*/  cra_module; } ;
struct aead_alg {int /*<<< orphan*/  exit; int /*<<< orphan*/  init; TYPE_1__ base; } ;
struct caam_aead_alg {struct aead_alg aead; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAAM_CRA_PRIORITY ; 
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_KERN_DRIVER_ONLY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  caam_aead_exit ; 
 int /*<<< orphan*/  caam_aead_init ; 

__attribute__((used)) static void caam_aead_alg_init(struct caam_aead_alg *t_alg)
{
	struct aead_alg *alg = &t_alg->aead;

	alg->base.cra_module = THIS_MODULE;
	alg->base.cra_priority = CAAM_CRA_PRIORITY;
	alg->base.cra_ctxsize = sizeof(struct caam_ctx);
	alg->base.cra_flags = CRYPTO_ALG_ASYNC | CRYPTO_ALG_KERN_DRIVER_ONLY;

	alg->init = caam_aead_init;
	alg->exit = caam_aead_exit;
}