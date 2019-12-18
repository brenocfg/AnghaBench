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
 int /*<<< orphan*/  _crypto_sign_ed25519_clamp (unsigned char*) ; 
 int /*<<< orphan*/  _crypto_sign_ed25519_ref10_hinit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _crypto_sign_ed25519_synthetic_r_hv (int /*<<< orphan*/ *,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_hash_sha512 (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  crypto_hash_sha512_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  crypto_hash_sha512_update (int /*<<< orphan*/ *,unsigned char const*,unsigned long long) ; 
 int /*<<< orphan*/  ge25519_p3_tobytes (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_scalarmult_base (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  sc25519_muladd (unsigned char*,unsigned char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  sc25519_reduce (unsigned char*) ; 
 int /*<<< orphan*/  sodium_memzero (unsigned char*,int) ; 

int
_crypto_sign_ed25519_detached(unsigned char *sig, unsigned long long *siglen_p,
                              const unsigned char *m, unsigned long long mlen,
                              const unsigned char *sk, int prehashed)
{
    crypto_hash_sha512_state hs;
    unsigned char            az[64];
    unsigned char            nonce[64];
    unsigned char            hram[64];
    ge25519_p3               R;

    _crypto_sign_ed25519_ref10_hinit(&hs, prehashed);

    crypto_hash_sha512(az, sk, 32);
#ifdef ED25519_NONDETERMINISTIC
    _crypto_sign_ed25519_synthetic_r_hv(&hs, nonce /* Z */, az);
#else
    crypto_hash_sha512_update(&hs, az + 32, 32);
#endif

    crypto_hash_sha512_update(&hs, m, mlen);
    crypto_hash_sha512_final(&hs, nonce);

    memmove(sig + 32, sk + 32, 32);

    sc25519_reduce(nonce);
    ge25519_scalarmult_base(&R, nonce);
    ge25519_p3_tobytes(sig, &R);

    _crypto_sign_ed25519_ref10_hinit(&hs, prehashed);
    crypto_hash_sha512_update(&hs, sig, 64);
    crypto_hash_sha512_update(&hs, m, mlen);
    crypto_hash_sha512_final(&hs, hram);

    sc25519_reduce(hram);
    _crypto_sign_ed25519_clamp(az);
    sc25519_muladd(sig + 32, hram, az, nonce);

    sodium_memzero(az, sizeof az);
    sodium_memzero(nonce, sizeof nonce);

    if (siglen_p != NULL) {
        *siglen_p = 64U;
    }
    return 0;
}