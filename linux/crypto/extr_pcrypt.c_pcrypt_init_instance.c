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
struct TYPE_2__ {int /*<<< orphan*/  cra_alignmask; int /*<<< orphan*/  cra_blocksize; scalar_t__ cra_priority; int /*<<< orphan*/  cra_name; int /*<<< orphan*/  cra_driver_name; } ;
struct crypto_instance {TYPE_1__ alg; } ;
struct crypto_alg {char* cra_driver_name; int /*<<< orphan*/  cra_alignmask; int /*<<< orphan*/  cra_blocksize; scalar_t__ cra_priority; int /*<<< orphan*/  cra_name; } ;

/* Variables and functions */
 scalar_t__ CRYPTO_MAX_ALG_NAME ; 
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ snprintf (int /*<<< orphan*/ ,scalar_t__,char*,char*) ; 

__attribute__((used)) static int pcrypt_init_instance(struct crypto_instance *inst,
				struct crypto_alg *alg)
{
	if (snprintf(inst->alg.cra_driver_name, CRYPTO_MAX_ALG_NAME,
		     "pcrypt(%s)", alg->cra_driver_name) >= CRYPTO_MAX_ALG_NAME)
		return -ENAMETOOLONG;

	memcpy(inst->alg.cra_name, alg->cra_name, CRYPTO_MAX_ALG_NAME);

	inst->alg.cra_priority = alg->cra_priority + 100;
	inst->alg.cra_blocksize = alg->cra_blocksize;
	inst->alg.cra_alignmask = alg->cra_alignmask;

	return 0;
}