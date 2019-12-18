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

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__* aes_algs ; 
 scalar_t__* aes_simd_algs ; 
 int /*<<< orphan*/  crypto_unregister_skciphers (scalar_t__*,int) ; 
 int /*<<< orphan*/  simd_skcipher_free (scalar_t__) ; 

__attribute__((used)) static void aes_exit(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(aes_simd_algs); i++)
		if (aes_simd_algs[i])
			simd_skcipher_free(aes_simd_algs[i]);

	crypto_unregister_skciphers(aes_algs, ARRAY_SIZE(aes_algs));
}