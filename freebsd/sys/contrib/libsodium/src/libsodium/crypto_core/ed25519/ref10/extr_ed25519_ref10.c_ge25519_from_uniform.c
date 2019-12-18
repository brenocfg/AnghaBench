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
typedef  int /*<<< orphan*/ * fe25519 ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  chi25519 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curve25519_A ; 
 int /*<<< orphan*/  fe25519_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_cmov (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  fe25519_frombytes (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  fe25519_invert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_neg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_sq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_sq2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_tobytes (unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ge25519_frombytes (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  ge25519_p1p1_to_p2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p1p1_to_p3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p2_dbl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p3_dbl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p3_tobytes (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

void
ge25519_from_uniform(unsigned char s[32], const unsigned char r[32])
{
    fe25519       e;
    fe25519       negx;
    fe25519       rr2;
    fe25519       x, x2, x3;
    ge25519_p3    p3;
    ge25519_p1p1  p1;
    ge25519_p2    p2;
    unsigned int  e_is_minus_1;
    unsigned char x_sign;

    memcpy(s, r, 32);
    x_sign = s[31] & 0x80;
    s[31] &= 0x7f;

    fe25519_frombytes(rr2, s);

    /* elligator */
    fe25519_sq2(rr2, rr2);
    rr2[0]++;
    fe25519_invert(rr2, rr2);
    fe25519_mul(x, curve25519_A, rr2);
    fe25519_neg(x, x);

    fe25519_sq(x2, x);
    fe25519_mul(x3, x, x2);
    fe25519_add(e, x3, x);
    fe25519_mul(x2, x2, curve25519_A);
    fe25519_add(e, x2, e);

    chi25519(e, e);

    fe25519_tobytes(s, e);
    e_is_minus_1 = s[1] & 1;
    fe25519_neg(negx, x);
    fe25519_cmov(x, negx, e_is_minus_1);
    fe25519_0(x2);
    fe25519_cmov(x2, curve25519_A, e_is_minus_1);
    fe25519_sub(x, x, x2);

    /* yed = (x-1)/(x+1) */
    {
        fe25519 one;
        fe25519 x_plus_one;
        fe25519 x_plus_one_inv;
        fe25519 x_minus_one;
        fe25519 yed;

        fe25519_1(one);
        fe25519_add(x_plus_one, x, one);
        fe25519_sub(x_minus_one, x, one);
        fe25519_invert(x_plus_one_inv, x_plus_one);
        fe25519_mul(yed, x_minus_one, x_plus_one_inv);
        fe25519_tobytes(s, yed);
    }

    /* recover x */
    s[31] |= x_sign;
    if (ge25519_frombytes(&p3, s) != 0) {
        abort(); /* LCOV_EXCL_LINE */
    }

    /* multiply by the cofactor */
    ge25519_p3_dbl(&p1, &p3);
    ge25519_p1p1_to_p2(&p2, &p1);
    ge25519_p2_dbl(&p1, &p2);
    ge25519_p1p1_to_p2(&p2, &p1);
    ge25519_p2_dbl(&p1, &p2);
    ge25519_p1p1_to_p3(&p3, &p1);

    ge25519_p3_tobytes(s, &p3);
}