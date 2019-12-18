#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_gej ;
struct TYPE_4__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_ecmult_gen_context ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY_CHECK (int) ; 
 int /*<<< orphan*/  secp256k1_ecmult_gen (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  secp256k1_fe_get_b32 (unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_fe_is_odd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_normalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ge_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  secp256k1_ge_set_gej (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_add (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  secp256k1_scalar_clear (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  secp256k1_scalar_inverse (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ secp256k1_scalar_is_high (int /*<<< orphan*/  const*) ; 
 scalar_t__ secp256k1_scalar_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  secp256k1_scalar_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  secp256k1_scalar_negate (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_b32 (int /*<<< orphan*/  const*,unsigned char*,int*) ; 

__attribute__((used)) static int secp256k1_ecdsa_sig_sign(const secp256k1_ecmult_gen_context *ctx, secp256k1_scalar *sigr, secp256k1_scalar *sigs, const secp256k1_scalar *seckey, const secp256k1_scalar *message, const secp256k1_scalar *nonce, int *recid) {
    unsigned char b[32];
    secp256k1_gej rp;
    secp256k1_ge r;
    secp256k1_scalar n;
    int overflow = 0;

    secp256k1_ecmult_gen(ctx, &rp, nonce);
    secp256k1_ge_set_gej(&r, &rp);
    secp256k1_fe_normalize(&r.x);
    secp256k1_fe_normalize(&r.y);
    secp256k1_fe_get_b32(b, &r.x);
    secp256k1_scalar_set_b32(sigr, b, &overflow);
    /* These two conditions should be checked before calling */
    VERIFY_CHECK(!secp256k1_scalar_is_zero(sigr));
    VERIFY_CHECK(overflow == 0);

    if (recid) {
        /* The overflow condition is cryptographically unreachable as hitting it requires finding the discrete log
         * of some P where P.x >= order, and only 1 in about 2^127 points meet this criteria.
         */
        *recid = (overflow ? 2 : 0) | (secp256k1_fe_is_odd(&r.y) ? 1 : 0);
    }
    secp256k1_scalar_mul(&n, sigr, seckey);
    secp256k1_scalar_add(&n, &n, message);
    secp256k1_scalar_inverse(sigs, nonce);
    secp256k1_scalar_mul(sigs, sigs, &n);
    secp256k1_scalar_clear(&n);
    secp256k1_gej_clear(&rp);
    secp256k1_ge_clear(&r);
    if (secp256k1_scalar_is_zero(sigs)) {
        return 0;
    }
    if (secp256k1_scalar_is_high(sigs)) {
        secp256k1_scalar_negate(sigs, sigs);
        if (recid) {
            *recid ^= 1;
        }
    }
    return 1;
}