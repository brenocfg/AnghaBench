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
struct TYPE_2__ {int /*<<< orphan*/  cra_driver_name; int /*<<< orphan*/  cra_name; } ;
struct crypto_instance {TYPE_1__ alg; } ;
struct crypto_alg {char* cra_name; char* cra_driver_name; } ;

/* Variables and functions */
 scalar_t__ CRYPTO_MAX_ALG_NAME ; 
 int ENAMETOOLONG ; 
 scalar_t__ snprintf (int /*<<< orphan*/ ,scalar_t__,char*,char const*,char*) ; 

int crypto_inst_setname(struct crypto_instance *inst, const char *name,
			struct crypto_alg *alg)
{
	if (snprintf(inst->alg.cra_name, CRYPTO_MAX_ALG_NAME, "%s(%s)", name,
		     alg->cra_name) >= CRYPTO_MAX_ALG_NAME)
		return -ENAMETOOLONG;

	if (snprintf(inst->alg.cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s(%s)",
		     name, alg->cra_driver_name) >= CRYPTO_MAX_ALG_NAME)
		return -ENAMETOOLONG;

	return 0;
}