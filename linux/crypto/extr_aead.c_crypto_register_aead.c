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
struct crypto_alg {int dummy; } ;
struct aead_alg {struct crypto_alg base; } ;

/* Variables and functions */
 int aead_prepare_alg (struct aead_alg*) ; 
 int crypto_register_alg (struct crypto_alg*) ; 

int crypto_register_aead(struct aead_alg *alg)
{
	struct crypto_alg *base = &alg->base;
	int err;

	err = aead_prepare_alg(alg);
	if (err)
		return err;

	return crypto_register_alg(base);
}