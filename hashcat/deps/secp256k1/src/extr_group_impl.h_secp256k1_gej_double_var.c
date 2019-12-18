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
struct TYPE_4__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  z; scalar_t__ infinity; } ;
typedef  TYPE_1__ secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_fe ;

/* Variables and functions */
 int /*<<< orphan*/  secp256k1_fe_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_mul_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_fe_negate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_fe_normalize_weak (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_set_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  secp256k1_fe_sqr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void secp256k1_gej_double_var(secp256k1_gej *r, const secp256k1_gej *a, secp256k1_fe *rzr) {
    /* Operations: 3 mul, 4 sqr, 0 normalize, 12 mul_int/add/negate.
     *
     * Note that there is an implementation described at
     *     https://hyperelliptic.org/EFD/g1p/auto-shortw-jacobian-0.html#doubling-dbl-2009-l
     * which trades a multiply for a square, but in practice this is actually slower,
     * mainly because it requires more normalizations.
     */
    secp256k1_fe t1,t2,t3,t4;
    /** For secp256k1, 2Q is infinity if and only if Q is infinity. This is because if 2Q = infinity,
     *  Q must equal -Q, or that Q.y == -(Q.y), or Q.y is 0. For a point on y^2 = x^3 + 7 to have
     *  y=0, x^3 must be -7 mod p. However, -7 has no cube root mod p.
     *
     *  Having said this, if this function receives a point on a sextic twist, e.g. by
     *  a fault attack, it is possible for y to be 0. This happens for y^2 = x^3 + 6,
     *  since -6 does have a cube root mod p. For this point, this function will not set
     *  the infinity flag even though the point doubles to infinity, and the result
     *  point will be gibberish (z = 0 but infinity = 0).
     */
    r->infinity = a->infinity;
    if (r->infinity) {
        if (rzr != NULL) {
            secp256k1_fe_set_int(rzr, 1);
        }
        return;
    }

    if (rzr != NULL) {
        *rzr = a->y;
        secp256k1_fe_normalize_weak(rzr);
        secp256k1_fe_mul_int(rzr, 2);
    }

    secp256k1_fe_mul(&r->z, &a->z, &a->y);
    secp256k1_fe_mul_int(&r->z, 2);       /* Z' = 2*Y*Z (2) */
    secp256k1_fe_sqr(&t1, &a->x);
    secp256k1_fe_mul_int(&t1, 3);         /* T1 = 3*X^2 (3) */
    secp256k1_fe_sqr(&t2, &t1);           /* T2 = 9*X^4 (1) */
    secp256k1_fe_sqr(&t3, &a->y);
    secp256k1_fe_mul_int(&t3, 2);         /* T3 = 2*Y^2 (2) */
    secp256k1_fe_sqr(&t4, &t3);
    secp256k1_fe_mul_int(&t4, 2);         /* T4 = 8*Y^4 (2) */
    secp256k1_fe_mul(&t3, &t3, &a->x);    /* T3 = 2*X*Y^2 (1) */
    r->x = t3;
    secp256k1_fe_mul_int(&r->x, 4);       /* X' = 8*X*Y^2 (4) */
    secp256k1_fe_negate(&r->x, &r->x, 4); /* X' = -8*X*Y^2 (5) */
    secp256k1_fe_add(&r->x, &t2);         /* X' = 9*X^4 - 8*X*Y^2 (6) */
    secp256k1_fe_negate(&t2, &t2, 1);     /* T2 = -9*X^4 (2) */
    secp256k1_fe_mul_int(&t3, 6);         /* T3 = 12*X*Y^2 (6) */
    secp256k1_fe_add(&t3, &t2);           /* T3 = 12*X*Y^2 - 9*X^4 (8) */
    secp256k1_fe_mul(&r->y, &t1, &t3);    /* Y' = 36*X^3*Y^2 - 27*X^6 (1) */
    secp256k1_fe_negate(&t2, &t4, 2);     /* T2 = -8*Y^4 (3) */
    secp256k1_fe_add(&r->y, &t2);         /* Y' = 36*X^3*Y^2 - 27*X^6 - 8*Y^4 (4) */
}