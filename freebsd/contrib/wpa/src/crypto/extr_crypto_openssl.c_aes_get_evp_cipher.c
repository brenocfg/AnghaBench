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
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  const* EVP_aes_128_ecb () ; 
 int /*<<< orphan*/  const* EVP_aes_192_ecb () ; 
 int /*<<< orphan*/  const* EVP_aes_256_ecb () ; 

__attribute__((used)) static const EVP_CIPHER * aes_get_evp_cipher(size_t keylen)
{
	switch (keylen) {
	case 16:
		return EVP_aes_128_ecb();
	case 24:
		return EVP_aes_192_ecb();
	case 32:
		return EVP_aes_256_ecb();
	}

	return NULL;
}