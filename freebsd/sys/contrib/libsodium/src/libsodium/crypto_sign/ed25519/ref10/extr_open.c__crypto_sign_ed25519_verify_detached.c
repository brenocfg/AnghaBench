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
typedef  int /*<<< orphan*/  crypto_hash_sha512_state ;

/* Variables and functions */
 int /*<<< orphan*/  _crypto_sign_ed25519_ref10_hinit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crypto_hash_sha512_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  crypto_hash_sha512_update (int /*<<< orphan*/ *,unsigned char const*,unsigned long long) ; 
 int crypto_verify_32 (unsigned char*,unsigned char const*) ; 
 int /*<<< orphan*/  ge25519_double_scalarmult_vartime (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *,unsigned char const*) ; 
 scalar_t__ ge25519_frombytes_negate_vartime (int /*<<< orphan*/ *,unsigned char const*) ; 
 scalar_t__ ge25519_has_small_order (unsigned char const*) ; 
 scalar_t__ ge25519_is_canonical (unsigned char const*) ; 
 int /*<<< orphan*/  ge25519_tobytes (unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ sc25519_is_canonical (unsigned char const*) ; 
 int /*<<< orphan*/  sc25519_reduce (unsigned char*) ; 
 int sodium_memcmp (unsigned char const*,unsigned char*,int) ; 

int
_crypto_sign_ed25519_verify_detached(const unsigned char *sig,
                                     const unsigned char *m,
                                     unsigned long long   mlen,
                                     const unsigned char *pk,
                                     int prehashed)
{
    crypto_hash_sha512_state hs;
    unsigned char            h[64];
    unsigned char            rcheck[32];
    ge25519_p3               A;
    ge25519_p2               R;

#ifdef ED25519_COMPAT
    if (sig[63] & 224) {
        return -1;
    }
#else
    if (sc25519_is_canonical(sig + 32) == 0 ||
        ge25519_has_small_order(sig) != 0) {
        return -1;
    }
    if (ge25519_is_canonical(pk) == 0 ||
        ge25519_has_small_order(pk) != 0) {
        return -1;
    }
#endif
    if (ge25519_frombytes_negate_vartime(&A, pk) != 0) {
        return -1;
    }
    _crypto_sign_ed25519_ref10_hinit(&hs, prehashed);
    crypto_hash_sha512_update(&hs, sig, 32);
    crypto_hash_sha512_update(&hs, pk, 32);
    crypto_hash_sha512_update(&hs, m, mlen);
    crypto_hash_sha512_final(&hs, h);
    sc25519_reduce(h);

    ge25519_double_scalarmult_vartime(&R, h, &A, sig + 32);
    ge25519_tobytes(rcheck, &R);

    return crypto_verify_32(rcheck, sig) | (-(rcheck == sig)) |
           sodium_memcmp(sig, rcheck, 32);
}