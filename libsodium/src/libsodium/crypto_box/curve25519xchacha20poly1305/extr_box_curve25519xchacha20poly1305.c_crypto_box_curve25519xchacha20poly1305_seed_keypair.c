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
 int crypto_scalarmult_curve25519_base (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  sodium_memzero (unsigned char*,int) ; 

int
crypto_box_curve25519xchacha20poly1305_seed_keypair(unsigned char *pk,
                                                    unsigned char *sk,
                                                    const unsigned char *seed)
{
    unsigned char hash[64];

    crypto_hash_sha512(hash, seed, 32);
    memcpy(sk, hash, 32);
    sodium_memzero(hash, sizeof hash);

    return crypto_scalarmult_curve25519_base(pk, sk);
}