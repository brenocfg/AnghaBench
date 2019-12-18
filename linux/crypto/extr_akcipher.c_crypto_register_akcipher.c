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
struct akcipher_alg {void* decrypt; void* encrypt; void* verify; void* sign; struct crypto_alg base; } ;

/* Variables and functions */
 void* akcipher_default_op ; 
 int /*<<< orphan*/  akcipher_prepare_alg (struct akcipher_alg*) ; 
 int crypto_register_alg (struct crypto_alg*) ; 

int crypto_register_akcipher(struct akcipher_alg *alg)
{
	struct crypto_alg *base = &alg->base;

	if (!alg->sign)
		alg->sign = akcipher_default_op;
	if (!alg->verify)
		alg->verify = akcipher_default_op;
	if (!alg->encrypt)
		alg->encrypt = akcipher_default_op;
	if (!alg->decrypt)
		alg->decrypt = akcipher_default_op;

	akcipher_prepare_alg(alg);
	return crypto_register_alg(base);
}