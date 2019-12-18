#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct shash_instance {int /*<<< orphan*/  alg; } ;
struct crypto_template {int dummy; } ;

/* Variables and functions */
 int crypto_register_instance (struct crypto_template*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shash_crypto_instance (struct shash_instance*) ; 
 int shash_prepare_alg (int /*<<< orphan*/ *) ; 

int shash_register_instance(struct crypto_template *tmpl,
			    struct shash_instance *inst)
{
	int err;

	err = shash_prepare_alg(&inst->alg);
	if (err)
		return err;

	return crypto_register_instance(tmpl, shash_crypto_instance(inst));
}