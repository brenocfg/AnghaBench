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
struct crypto_template {int dummy; } ;
struct crypto_instance {struct crypto_template* tmpl; } ;
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_instance (struct crypto_instance*) ; 
 int /*<<< orphan*/  crypto_tmpl_put (struct crypto_template*) ; 

__attribute__((used)) static void crypto_destroy_instance(struct crypto_alg *alg)
{
	struct crypto_instance *inst = (void *)alg;
	struct crypto_template *tmpl = inst->tmpl;

	crypto_free_instance(inst);
	crypto_tmpl_put(tmpl);
}