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
struct caam_skcipher_alg {int /*<<< orphan*/  skcipher; scalar_t__ registered; } ;
struct caam_aead_alg {int /*<<< orphan*/  aead; scalar_t__ registered; } ;

/* Variables and functions */
 int ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  crypto_unregister_aead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_skcipher (int /*<<< orphan*/ *) ; 
 void* driver_aeads ; 
 void* driver_algs ; 

void caam_qi_algapi_exit(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(driver_aeads); i++) {
		struct caam_aead_alg *t_alg = driver_aeads + i;

		if (t_alg->registered)
			crypto_unregister_aead(&t_alg->aead);
	}

	for (i = 0; i < ARRAY_SIZE(driver_algs); i++) {
		struct caam_skcipher_alg *t_alg = driver_algs + i;

		if (t_alg->registered)
			crypto_unregister_skcipher(&t_alg->skcipher);
	}
}