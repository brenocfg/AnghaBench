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
struct alg {int cipher; } ;

/* Variables and functions */
#define  CRYPTO_AES_ICM 129 
#define  CRYPTO_AES_XTS 128 
 char* alloc_buffer (size_t) ; 

__attribute__((used)) static char *
generate_iv(size_t len, struct alg *alg)
{
	char *iv;

	iv = alloc_buffer(len);
	switch (alg->cipher) {
	case CRYPTO_AES_ICM:
		/* Clear the low 32 bits of the IV to hold the counter. */
		iv[len - 4] = 0;
		iv[len - 3] = 0;
		iv[len - 2] = 0;
		iv[len - 1] = 0;
		break;
	case CRYPTO_AES_XTS:
		/*
		 * Clear the low 64-bits to only store a 64-bit block
		 * number.
		 */
		iv[len - 8] = 0;
		iv[len - 7] = 0;
		iv[len - 6] = 0;
		iv[len - 5] = 0;
		iv[len - 4] = 0;
		iv[len - 3] = 0;
		iv[len - 2] = 0;
		iv[len - 1] = 0;
		break;
	}
	return (iv);
}