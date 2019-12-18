#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hash; int /*<<< orphan*/  aead; int /*<<< orphan*/  crypto; } ;
struct TYPE_5__ {int type; scalar_t__ is_registered; TYPE_1__ alg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
#define  CRYPTO_ALG_TYPE_ABLKCIPHER 130 
#define  CRYPTO_ALG_TYPE_AEAD 129 
#define  CRYPTO_ALG_TYPE_AHASH 128 
 int CRYPTO_ALG_TYPE_MASK ; 
 int /*<<< orphan*/  crypto_unregister_aead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_ahash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 TYPE_2__* driver_algs ; 

__attribute__((used)) static int chcr_unregister_alg(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(driver_algs); i++) {
		switch (driver_algs[i].type & CRYPTO_ALG_TYPE_MASK) {
		case CRYPTO_ALG_TYPE_ABLKCIPHER:
			if (driver_algs[i].is_registered)
				crypto_unregister_alg(
						&driver_algs[i].alg.crypto);
			break;
		case CRYPTO_ALG_TYPE_AEAD:
			if (driver_algs[i].is_registered)
				crypto_unregister_aead(
						&driver_algs[i].alg.aead);
			break;
		case CRYPTO_ALG_TYPE_AHASH:
			if (driver_algs[i].is_registered)
				crypto_unregister_ahash(
						&driver_algs[i].alg.hash);
			break;
		}
		driver_algs[i].is_registered = 0;
	}
	return 0;
}