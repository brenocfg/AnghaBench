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
struct spu_hw {scalar_t__ spu_type; scalar_t__ spu_subtype; } ;
struct spu_hash_export_s {int dummy; } ;
struct iproc_ctx_s {int dummy; } ;
struct TYPE_7__ {scalar_t__ alg; scalar_t__ mode; } ;
struct TYPE_8__ {int cra_ctxsize; int /*<<< orphan*/  cra_driver_name; int /*<<< orphan*/  cra_flags; int /*<<< orphan*/  cra_exit; int /*<<< orphan*/  cra_init; scalar_t__ cra_alignmask; int /*<<< orphan*/  cra_priority; int /*<<< orphan*/  cra_module; } ;
struct TYPE_9__ {int statesize; TYPE_3__ base; } ;
struct ahash_alg {TYPE_4__ halg; int /*<<< orphan*/  import; int /*<<< orphan*/  export; int /*<<< orphan*/  digest; int /*<<< orphan*/  finup; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  init; int /*<<< orphan*/  setkey; } ;
struct TYPE_6__ {struct ahash_alg hash; } ;
struct iproc_alg_s {int registered; TYPE_2__ auth_info; TYPE_1__ alg; } ;
struct TYPE_10__ {struct spu_hw spu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 scalar_t__ HASH_ALG_AES ; 
 scalar_t__ HASH_ALG_SHA3_224 ; 
 scalar_t__ HASH_MODE_CMAC ; 
 scalar_t__ HASH_MODE_HMAC ; 
 scalar_t__ HASH_MODE_XCBC ; 
 scalar_t__ SPU_SUBTYPE_SPU2_V2 ; 
 scalar_t__ SPU_TYPE_SPUM ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ahash_cra_init ; 
 int /*<<< orphan*/  ahash_digest ; 
 int /*<<< orphan*/  ahash_export ; 
 int /*<<< orphan*/  ahash_final ; 
 int /*<<< orphan*/  ahash_finup ; 
 int /*<<< orphan*/  ahash_hmac_digest ; 
 int /*<<< orphan*/  ahash_hmac_final ; 
 int /*<<< orphan*/  ahash_hmac_finup ; 
 int /*<<< orphan*/  ahash_hmac_init ; 
 int /*<<< orphan*/  ahash_hmac_setkey ; 
 int /*<<< orphan*/  ahash_hmac_update ; 
 int /*<<< orphan*/  ahash_import ; 
 int /*<<< orphan*/  ahash_init ; 
 int /*<<< orphan*/  ahash_setkey ; 
 int /*<<< orphan*/  ahash_update ; 
 int crypto_register_ahash (struct ahash_alg*) ; 
 int /*<<< orphan*/  generic_cra_exit ; 
 int /*<<< orphan*/  hash_pri ; 
 TYPE_5__ iproc_priv ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spu_register_ahash(struct iproc_alg_s *driver_alg)
{
	struct spu_hw *spu = &iproc_priv.spu;
	struct ahash_alg *hash = &driver_alg->alg.hash;
	int err;

	/* AES-XCBC is the only AES hash type currently supported on SPU-M */
	if ((driver_alg->auth_info.alg == HASH_ALG_AES) &&
	    (driver_alg->auth_info.mode != HASH_MODE_XCBC) &&
	    (spu->spu_type == SPU_TYPE_SPUM))
		return 0;

	/* SHA3 algorithm variants are not registered for SPU-M or SPU2. */
	if ((driver_alg->auth_info.alg >= HASH_ALG_SHA3_224) &&
	    (spu->spu_subtype != SPU_SUBTYPE_SPU2_V2))
		return 0;

	hash->halg.base.cra_module = THIS_MODULE;
	hash->halg.base.cra_priority = hash_pri;
	hash->halg.base.cra_alignmask = 0;
	hash->halg.base.cra_ctxsize = sizeof(struct iproc_ctx_s);
	hash->halg.base.cra_init = ahash_cra_init;
	hash->halg.base.cra_exit = generic_cra_exit;
	hash->halg.base.cra_flags = CRYPTO_ALG_ASYNC;
	hash->halg.statesize = sizeof(struct spu_hash_export_s);

	if (driver_alg->auth_info.mode != HASH_MODE_HMAC) {
		hash->init = ahash_init;
		hash->update = ahash_update;
		hash->final = ahash_final;
		hash->finup = ahash_finup;
		hash->digest = ahash_digest;
		if ((driver_alg->auth_info.alg == HASH_ALG_AES) &&
		    ((driver_alg->auth_info.mode == HASH_MODE_XCBC) ||
		    (driver_alg->auth_info.mode == HASH_MODE_CMAC))) {
			hash->setkey = ahash_setkey;
		}
	} else {
		hash->setkey = ahash_hmac_setkey;
		hash->init = ahash_hmac_init;
		hash->update = ahash_hmac_update;
		hash->final = ahash_hmac_final;
		hash->finup = ahash_hmac_finup;
		hash->digest = ahash_hmac_digest;
	}
	hash->export = ahash_export;
	hash->import = ahash_import;

	err = crypto_register_ahash(hash);
	/* Mark alg as having been registered, if successful */
	if (err == 0)
		driver_alg->registered = true;
	pr_debug("  registered ahash %s\n",
		 hash->halg.base.cra_driver_name);
	return err;
}