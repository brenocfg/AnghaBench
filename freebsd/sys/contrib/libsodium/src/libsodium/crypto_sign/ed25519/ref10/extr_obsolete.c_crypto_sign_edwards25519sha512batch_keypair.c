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
 int /*<<< orphan*/  crypto_hash_sha512 (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  ge25519_p3_tobytes (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_scalarmult_base (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  randombytes_buf (unsigned char*,int) ; 

int
crypto_sign_edwards25519sha512batch_keypair(unsigned char *pk,
                                            unsigned char *sk)
{
    ge25519_p3 A;

    randombytes_buf(sk, 32);
    crypto_hash_sha512(sk, sk, 32);
    sk[0] &= 248;
    sk[31] &= 127;
    sk[31] |= 64;
    ge25519_scalarmult_base(&A, sk);
    ge25519_p3_tobytes(pk, &A);

    return 0;
}