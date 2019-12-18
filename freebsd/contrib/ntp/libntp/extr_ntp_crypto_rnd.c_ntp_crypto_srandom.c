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
 int /*<<< orphan*/  RAND_poll () ; 
 int crypto_rand_init ; 

void
ntp_crypto_srandom(
	void
	)
{
#ifdef USE_OPENSSL_CRYPTO_RAND
	if (!crypto_rand_init) {
		RAND_poll();
		crypto_rand_init = 1;
	}
#else
	/* No initialization needed for arc4random() */
#endif
}