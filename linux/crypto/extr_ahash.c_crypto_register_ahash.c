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
struct crypto_alg {int dummy; } ;
struct TYPE_2__ {struct crypto_alg base; } ;
struct ahash_alg {TYPE_1__ halg; } ;

/* Variables and functions */
 int ahash_prepare_alg (struct ahash_alg*) ; 
 int crypto_register_alg (struct crypto_alg*) ; 

int crypto_register_ahash(struct ahash_alg *alg)
{
	struct crypto_alg *base = &alg->halg.base;
	int err;

	err = ahash_prepare_alg(alg);
	if (err)
		return err;

	return crypto_register_alg(base);
}