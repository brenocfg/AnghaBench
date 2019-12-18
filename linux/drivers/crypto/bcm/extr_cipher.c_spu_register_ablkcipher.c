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
struct spu_hw {scalar_t__ spu_type; } ;
struct iproc_ctx_s {int dummy; } ;
struct TYPE_6__ {scalar_t__ alg; } ;
struct TYPE_7__ {int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setkey; } ;
struct crypto_alg {int cra_ctxsize; int cra_flags; int /*<<< orphan*/  cra_driver_name; TYPE_3__ cra_ablkcipher; int /*<<< orphan*/ * cra_type; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; scalar_t__ cra_alignmask; int /*<<< orphan*/  cra_priority; int /*<<< orphan*/  cra_module; } ;
struct TYPE_5__ {struct crypto_alg crypto; } ;
struct iproc_alg_s {int registered; TYPE_2__ cipher_info; TYPE_1__ alg; } ;
struct TYPE_8__ {struct spu_hw spu; } ;

/* Variables and functions */
 scalar_t__ CIPHER_ALG_RC4 ; 
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_KERN_DRIVER_ONLY ; 
 int CRYPTO_ALG_TYPE_ABLKCIPHER ; 
 scalar_t__ SPU_TYPE_SPU2 ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ablkcipher_cra_init ; 
 int /*<<< orphan*/  ablkcipher_decrypt ; 
 int /*<<< orphan*/  ablkcipher_encrypt ; 
 int /*<<< orphan*/  ablkcipher_setkey ; 
 int /*<<< orphan*/  cipher_pri ; 
 int /*<<< orphan*/  crypto_ablkcipher_type ; 
 int crypto_register_alg (struct crypto_alg*) ; 
 int /*<<< orphan*/  generic_cra_exit ; 
 TYPE_4__ iproc_priv ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spu_register_ablkcipher(struct iproc_alg_s *driver_alg)
{
	struct spu_hw *spu = &iproc_priv.spu;
	struct crypto_alg *crypto = &driver_alg->alg.crypto;
	int err;

	/* SPU2 does not support RC4 */
	if ((driver_alg->cipher_info.alg == CIPHER_ALG_RC4) &&
	    (spu->spu_type == SPU_TYPE_SPU2))
		return 0;

	crypto->cra_module = THIS_MODULE;
	crypto->cra_priority = cipher_pri;
	crypto->cra_alignmask = 0;
	crypto->cra_ctxsize = sizeof(struct iproc_ctx_s);

	crypto->cra_init = ablkcipher_cra_init;
	crypto->cra_exit = generic_cra_exit;
	crypto->cra_type = &crypto_ablkcipher_type;
	crypto->cra_flags = CRYPTO_ALG_TYPE_ABLKCIPHER | CRYPTO_ALG_ASYNC |
				CRYPTO_ALG_KERN_DRIVER_ONLY;

	crypto->cra_ablkcipher.setkey = ablkcipher_setkey;
	crypto->cra_ablkcipher.encrypt = ablkcipher_encrypt;
	crypto->cra_ablkcipher.decrypt = ablkcipher_decrypt;

	err = crypto_register_alg(crypto);
	/* Mark alg as having been registered, if successful */
	if (err == 0)
		driver_alg->registered = true;
	pr_debug("  registered ablkcipher %s\n", crypto->cra_driver_name);
	return err;
}