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
 int /*<<< orphan*/  crypto_hash_sha512 (unsigned char*,unsigned char const*,int) ; 
 int crypto_hash_sha512_BYTES ; 
 int crypto_scalarmult_curve25519_BYTES ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  sodium_memzero (unsigned char*,int) ; 

int
crypto_sign_ed25519_sk_to_curve25519(unsigned char *curve25519_sk,
                                     const unsigned char *ed25519_sk)
{
    unsigned char h[crypto_hash_sha512_BYTES];

#ifdef ED25519_NONDETERMINISTIC
    memcpy(h, ed25519_sk, 32);
#else
    crypto_hash_sha512(h, ed25519_sk, 32);
#endif
    h[0] &= 248;
    h[31] &= 127;
    h[31] |= 64;
    memcpy(curve25519_sk, h, crypto_scalarmult_curve25519_BYTES);
    sodium_memzero(h, sizeof h);

    return 0;
}