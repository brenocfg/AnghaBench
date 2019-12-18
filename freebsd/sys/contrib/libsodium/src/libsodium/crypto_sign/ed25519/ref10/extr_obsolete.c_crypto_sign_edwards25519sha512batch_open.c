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
typedef  int /*<<< orphan*/  ge25519_p2 ;
typedef  int /*<<< orphan*/  ge25519_p1p1 ;
typedef  int /*<<< orphan*/  ge25519_cached ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_hash_sha512 (unsigned char*,unsigned char const*,unsigned long long) ; 
 unsigned long long crypto_sign_edwards25519sha512batch_MESSAGEBYTES_MAX ; 
 scalar_t__ crypto_verify_32 (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  ge25519_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ge25519_frombytes_negate_vartime (int /*<<< orphan*/ *,unsigned char const*) ; 
 scalar_t__ ge25519_has_small_order (unsigned char const*) ; 
 int /*<<< orphan*/  ge25519_p1p1_to_p2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p3_to_cached (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p3_tobytes (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_scalarmult (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_scalarmult_base (int /*<<< orphan*/ *,unsigned char const*) ; 
 int /*<<< orphan*/  ge25519_tobytes (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char const*,unsigned long long) ; 
 int /*<<< orphan*/  sc25519_reduce (unsigned char*) ; 

int
crypto_sign_edwards25519sha512batch_open(unsigned char       *m,
                                         unsigned long long  *mlen_p,
                                         const unsigned char *sm,
                                         unsigned long long   smlen,
                                         const unsigned char *pk)
{
    unsigned char      h[64];
    unsigned char      t1[32], t2[32];
    unsigned long long mlen;
    ge25519_cached     Ai;
    ge25519_p1p1       csa;
    ge25519_p2         cs;
    ge25519_p3         A;
    ge25519_p3         R;
    ge25519_p3         cs3;

    *mlen_p = 0;
    if (smlen < 64 || smlen - 64 > crypto_sign_edwards25519sha512batch_MESSAGEBYTES_MAX) {
        return -1;
    }
    mlen = smlen - 64;
    if (sm[smlen - 1] & 224) {
        return -1;
    }
    if (ge25519_has_small_order(pk) != 0 ||
        ge25519_frombytes_negate_vartime(&A, pk) != 0 ||
        ge25519_has_small_order(sm) != 0 ||
        ge25519_frombytes_negate_vartime(&R, sm) != 0) {
        return -1;
    }
    ge25519_p3_to_cached(&Ai, &A);
    crypto_hash_sha512(h, sm, mlen + 32);
    sc25519_reduce(h);
    ge25519_scalarmult(&cs3, h, &R);
    ge25519_add(&csa, &cs3, &Ai);
    ge25519_p1p1_to_p2(&cs, &csa);
    ge25519_tobytes(t1, &cs);
    t1[31] ^= 1 << 7;
    ge25519_scalarmult_base(&R, sm + 32 + mlen);
    ge25519_p3_tobytes(t2, &R);
    if (crypto_verify_32(t1, t2) != 0) {
        return -1;
    }
    *mlen_p = mlen;
    memmove(m, sm + 32, mlen);

    return 0;
}