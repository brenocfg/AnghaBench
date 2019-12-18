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
typedef  int /*<<< orphan*/  ge25519_p3 ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_hash_sha512 (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  ge25519_p3_tobytes (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_scalarmult_base (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char const*,int) ; 

int
crypto_sign_ed25519_seed_keypair(unsigned char *pk, unsigned char *sk,
                                 const unsigned char *seed)
{
    ge25519_p3 A;

#ifdef ED25519_NONDETERMINISTIC
    memmove(sk, seed, 32);
#else
    crypto_hash_sha512(sk, seed, 32);
#endif
    sk[0] &= 248;
    sk[31] &= 127;
    sk[31] |= 64;

    ge25519_scalarmult_base(&A, sk);
    ge25519_p3_tobytes(pk, &A);

    memmove(sk, seed, 32);
    memmove(sk + 32, pk, 32);

    return 0;
}