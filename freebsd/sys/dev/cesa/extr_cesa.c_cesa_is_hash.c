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
#define  CRYPTO_MD5 132 
#define  CRYPTO_MD5_HMAC 131 
#define  CRYPTO_SHA1 130 
#define  CRYPTO_SHA1_HMAC 129 
#define  CRYPTO_SHA2_256_HMAC 128 

__attribute__((used)) static int
cesa_is_hash(int alg)
{

	switch (alg) {
	case CRYPTO_MD5:
	case CRYPTO_MD5_HMAC:
	case CRYPTO_SHA1:
	case CRYPTO_SHA1_HMAC:
	case CRYPTO_SHA2_256_HMAC:
		return (1);
	default:
		return (0);
	}
}