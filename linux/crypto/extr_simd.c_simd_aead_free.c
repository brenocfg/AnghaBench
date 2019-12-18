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
struct simd_aead_alg {int /*<<< orphan*/  alg; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_unregister_aead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct simd_aead_alg*) ; 

void simd_aead_free(struct simd_aead_alg *salg)
{
	crypto_unregister_aead(&salg->alg);
	kfree(salg);
}