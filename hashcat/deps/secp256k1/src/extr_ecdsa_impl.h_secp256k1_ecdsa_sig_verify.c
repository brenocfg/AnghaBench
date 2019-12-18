#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_gej ;
struct TYPE_5__ {int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_fe ;
typedef  int /*<<< orphan*/  secp256k1_ecmult_context ;

/* Variables and functions */
 int /*<<< orphan*/  secp256k1_ecdsa_const_order_as_fe ; 
 int /*<<< orphan*/  secp256k1_ecdsa_const_p_minus_order ; 
 int /*<<< orphan*/  secp256k1_ecmult (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_fe_cmp_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_get_b32 (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_normalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_set_b32 (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  secp256k1_ge_set_gej (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_gej_eq_x_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_gej_is_infinity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_set_ge (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int secp256k1_scalar_eq (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_get_b32 (unsigned char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  secp256k1_scalar_inverse_var (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ secp256k1_scalar_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  secp256k1_scalar_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_b32 (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int secp256k1_ecdsa_sig_verify(const secp256k1_ecmult_context *ctx, const secp256k1_scalar *sigr, const secp256k1_scalar *sigs, const secp256k1_ge *pubkey, const secp256k1_scalar *message) {
    unsigned char c[32];
    secp256k1_scalar sn, u1, u2;
#if !defined(EXHAUSTIVE_TEST_ORDER)
    secp256k1_fe xr;
#endif
    secp256k1_gej pubkeyj;
    secp256k1_gej pr;

    if (secp256k1_scalar_is_zero(sigr) || secp256k1_scalar_is_zero(sigs)) {
        return 0;
    }

    secp256k1_scalar_inverse_var(&sn, sigs);
    secp256k1_scalar_mul(&u1, &sn, message);
    secp256k1_scalar_mul(&u2, &sn, sigr);
    secp256k1_gej_set_ge(&pubkeyj, pubkey);
    secp256k1_ecmult(ctx, &pr, &pubkeyj, &u2, &u1);
    if (secp256k1_gej_is_infinity(&pr)) {
        return 0;
    }

#if defined(EXHAUSTIVE_TEST_ORDER)
{
    secp256k1_scalar computed_r;
    secp256k1_ge pr_ge;
    secp256k1_ge_set_gej(&pr_ge, &pr);
    secp256k1_fe_normalize(&pr_ge.x);

    secp256k1_fe_get_b32(c, &pr_ge.x);
    secp256k1_scalar_set_b32(&computed_r, c, NULL);
    return secp256k1_scalar_eq(sigr, &computed_r);
}
#else
    secp256k1_scalar_get_b32(c, sigr);
    secp256k1_fe_set_b32(&xr, c);

    /** We now have the recomputed R point in pr, and its claimed x coordinate (modulo n)
     *  in xr. Naively, we would extract the x coordinate from pr (requiring a inversion modulo p),
     *  compute the remainder modulo n, and compare it to xr. However:
     *
     *        xr == X(pr) mod n
     *    <=> exists h. (xr + h * n < p && xr + h * n == X(pr))
     *    [Since 2 * n > p, h can only be 0 or 1]
     *    <=> (xr == X(pr)) || (xr + n < p && xr + n == X(pr))
     *    [In Jacobian coordinates, X(pr) is pr.x / pr.z^2 mod p]
     *    <=> (xr == pr.x / pr.z^2 mod p) || (xr + n < p && xr + n == pr.x / pr.z^2 mod p)
     *    [Multiplying both sides of the equations by pr.z^2 mod p]
     *    <=> (xr * pr.z^2 mod p == pr.x) || (xr + n < p && (xr + n) * pr.z^2 mod p == pr.x)
     *
     *  Thus, we can avoid the inversion, but we have to check both cases separately.
     *  secp256k1_gej_eq_x implements the (xr * pr.z^2 mod p == pr.x) test.
     */
    if (secp256k1_gej_eq_x_var(&xr, &pr)) {
        /* xr * pr.z^2 mod p == pr.x, so the signature is valid. */
        return 1;
    }
    if (secp256k1_fe_cmp_var(&xr, &secp256k1_ecdsa_const_p_minus_order) >= 0) {
        /* xr + n >= p, so we can skip testing the second case. */
        return 0;
    }
    secp256k1_fe_add(&xr, &secp256k1_ecdsa_const_order_as_fe);
    if (secp256k1_gej_eq_x_var(&xr, &pr)) {
        /* (xr + n) * pr.z^2 mod p == pr.x, so the signature is valid. */
        return 1;
    }
    return 0;
#endif
}