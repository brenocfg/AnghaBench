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
struct crypto_aead {int dummy; } ;
struct aead_alg {int /*<<< orphan*/  (* exit ) (struct crypto_aead*) ;} ;

/* Variables and functions */
 struct crypto_aead* __crypto_aead_cast (struct crypto_tfm*) ; 
 struct aead_alg* crypto_aead_alg (struct crypto_aead*) ; 
 int /*<<< orphan*/  stub1 (struct crypto_aead*) ; 

__attribute__((used)) static void crypto_aead_exit_tfm(struct crypto_tfm *tfm)
{
	struct crypto_aead *aead = __crypto_aead_cast(tfm);
	struct aead_alg *alg = crypto_aead_alg(aead);

	alg->exit(aead);
}