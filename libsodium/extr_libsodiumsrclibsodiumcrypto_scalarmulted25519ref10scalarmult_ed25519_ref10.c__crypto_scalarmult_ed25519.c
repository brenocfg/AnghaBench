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
 int /*<<< orphan*/  _crypto_scalarmult_ed25519_clamp (unsigned char*) ; 
 scalar_t__ _crypto_scalarmult_ed25519_is_inf (unsigned char*) ; 
 scalar_t__ ge25519_frombytes (int /*<<< orphan*/ *,unsigned char const*) ; 
 scalar_t__ ge25519_has_small_order (unsigned char const*) ; 
 scalar_t__ ge25519_is_canonical (unsigned char const*) ; 
 scalar_t__ ge25519_is_on_main_subgroup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p3_tobytes (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_scalarmult (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ sodium_is_zero (unsigned char const*,int) ; 

__attribute__((used)) static int
_crypto_scalarmult_ed25519(unsigned char *q, const unsigned char *n,
                           const unsigned char *p, const int clamp)
{
    unsigned char *t = q;
    ge25519_p3     Q;
    ge25519_p3     P;
    unsigned int   i;

    if (ge25519_is_canonical(p) == 0 || ge25519_has_small_order(p) != 0 ||
        ge25519_frombytes(&P, p) != 0 || ge25519_is_on_main_subgroup(&P) == 0) {
        return -1;
    }
    for (i = 0; i < 32; ++i) {
        t[i] = n[i];
    }
    if (clamp != 0) {
        _crypto_scalarmult_ed25519_clamp(t);
    }
    t[31] &= 127;

    ge25519_scalarmult(&Q, t, &P);
    ge25519_p3_tobytes(q, &Q);
    if (_crypto_scalarmult_ed25519_is_inf(q) != 0 || sodium_is_zero(n, 32)) {
        return -1;
    }
    return 0;
}