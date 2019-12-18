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
struct crypto_tfm {int dummy; } ;
struct crypto_acomp {int dummy; } ;
struct acomp_alg {int /*<<< orphan*/  (* exit ) (struct crypto_acomp*) ;} ;

/* Variables and functions */
 struct crypto_acomp* __crypto_acomp_tfm (struct crypto_tfm*) ; 
 struct acomp_alg* crypto_acomp_alg (struct crypto_acomp*) ; 
 int /*<<< orphan*/  stub1 (struct crypto_acomp*) ; 

__attribute__((used)) static void crypto_acomp_exit_tfm(struct crypto_tfm *tfm)
{
	struct crypto_acomp *acomp = __crypto_acomp_tfm(tfm);
	struct acomp_alg *alg = crypto_acomp_alg(acomp);

	alg->exit(acomp);
}