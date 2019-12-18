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
struct simd_aead_alg {int dummy; } ;
struct aead_alg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_unregister_aeads (struct aead_alg*,int) ; 
 int /*<<< orphan*/  simd_aead_free (struct simd_aead_alg*) ; 

void simd_unregister_aeads(struct aead_alg *algs, int count,
			   struct simd_aead_alg **simd_algs)
{
	int i;

	crypto_unregister_aeads(algs, count);

	for (i = 0; i < count; i++) {
		if (simd_algs[i]) {
			simd_aead_free(simd_algs[i]);
			simd_algs[i] = NULL;
		}
	}
}