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
typedef  int /*<<< orphan*/  crypto_hash_sha512_state ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_hash_sha512_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  crypto_hash_sha512_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_hash_sha512_update (int /*<<< orphan*/ *,unsigned char const*,unsigned long long) ; 
 int /*<<< orphan*/  ge25519_p3_tobytes (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_scalarmult_base (int /*<<< orphan*/ *,unsigned char const*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  sc25519_muladd (unsigned char*,unsigned char*,unsigned char*,unsigned char const*) ; 
 int /*<<< orphan*/  sc25519_reduce (unsigned char*) ; 
 int /*<<< orphan*/  sodium_memzero (unsigned char*,int) ; 

int
crypto_sign_edwards25519sha512batch(unsigned char       *sm,
                                    unsigned long long  *smlen_p,
                                    const unsigned char *m,
                                    unsigned long long   mlen,
                                    const unsigned char *sk)
{
    crypto_hash_sha512_state hs;
    unsigned char            nonce[64];
    unsigned char            hram[64];
    unsigned char            sig[64];
    ge25519_p3               A;
    ge25519_p3               R;

    crypto_hash_sha512_init(&hs);
    crypto_hash_sha512_update(&hs, sk + 32, 32);
    crypto_hash_sha512_update(&hs, m, mlen);
    crypto_hash_sha512_final(&hs, nonce);
    ge25519_scalarmult_base(&A, sk);
    ge25519_p3_tobytes(sig + 32, &A);
    sc25519_reduce(nonce);
    ge25519_scalarmult_base(&R, nonce);
    ge25519_p3_tobytes(sig, &R);
    crypto_hash_sha512_init(&hs);
    crypto_hash_sha512_update(&hs, sig, 32);
    crypto_hash_sha512_update(&hs, m, mlen);
    crypto_hash_sha512_final(&hs, hram);
    sc25519_reduce(hram);
    sc25519_muladd(sig + 32, hram, nonce, sk);
    sodium_memzero(hram, sizeof hram);
    memmove(sm + 32, m, (size_t) mlen);
    memcpy(sm, sig, 32);
    memcpy(sm + 32 + mlen, sig + 32, 32);
    *smlen_p = mlen + 64U;

    return 0;
}