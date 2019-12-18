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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ crypto_mod_exp (scalar_t__*,int,scalar_t__*,size_t,scalar_t__ const*,size_t,scalar_t__*,size_t*) ; 
 scalar_t__ os_get_random (scalar_t__*,size_t) ; 
 scalar_t__ os_memcmp (scalar_t__*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  os_memmove (scalar_t__*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  os_memset (scalar_t__*,int /*<<< orphan*/ ,size_t) ; 

int crypto_dh_init(u8 generator, const u8 *prime, size_t prime_len, u8 *privkey,
		   u8 *pubkey)
{
	size_t pubkey_len, pad;

	if (os_get_random(privkey, prime_len) < 0)
		return -1;
	if (os_memcmp(privkey, prime, prime_len) > 0) {
		/* Make sure private value is smaller than prime */
		privkey[0] = 0;
	}

	pubkey_len = prime_len;
	if (crypto_mod_exp(&generator, 1, privkey, prime_len, prime, prime_len,
			   pubkey, &pubkey_len) < 0)
		return -1;
	if (pubkey_len < prime_len) {
		pad = prime_len - pubkey_len;
		os_memmove(pubkey + pad, pubkey, pubkey_len);
		os_memset(pubkey, 0, pad);
	}

	return 0;
}