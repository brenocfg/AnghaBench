#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; int /*<<< orphan*/  T; } ;
typedef  TYPE_1__ ge25519_p3 ;
typedef  int /*<<< orphan*/  fe25519 ;

/* Variables and functions */
 int /*<<< orphan*/  fe25519_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_cmov (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fe25519_cneg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fe25519_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fe25519_isnegative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_sq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_tobytes (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invsqrtamd ; 
 int /*<<< orphan*/  ristretto255_sqrt_ratio_m1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqrtm1 ; 

void
ristretto255_p3_tobytes(unsigned char *s, const ge25519_p3 *h)
{
    fe25519 den1, den2;
    fe25519 den_inv;
    fe25519 eden;
    fe25519 inv_sqrt;
    fe25519 ix, iy;
    fe25519 one;
    fe25519 s_;
    fe25519 t_z_inv;
    fe25519 u1, u2;
    fe25519 u1_u2u2;
    fe25519 x_, y_;
    fe25519 x_z_inv;
    fe25519 z_inv;
    fe25519 zmy;
    int     rotate;

    fe25519_add(u1, h->Z, h->Y);       /* u1 = Z+Y */
    fe25519_sub(zmy, h->Z, h->Y);      /* zmy = Z-Y */
    fe25519_mul(u1, u1, zmy);          /* u1 = (Z+Y)*(Z-Y) */
    fe25519_mul(u2, h->X, h->Y);       /* u2 = X*Y */

    fe25519_sq(u1_u2u2, u2);           /* u1_u2u2 = u2^2 */
    fe25519_mul(u1_u2u2, u1, u1_u2u2); /* u1_u2u2 = u1*u2^2 */

    fe25519_1(one);
    (void) ristretto255_sqrt_ratio_m1(inv_sqrt, one, u1_u2u2);
    fe25519_mul(den1, inv_sqrt, u1);   /* den1 = inv_sqrt*u1 */
    fe25519_mul(den2, inv_sqrt, u2);   /* den2 = inv_sqrt*u2 */
    fe25519_mul(z_inv, den1, den2);    /* z_inv = den1*den2 */
    fe25519_mul(z_inv, z_inv, h->T);   /* z_inv = den1*den2*T */

    fe25519_mul(ix, h->X, sqrtm1);     /* ix = X*sqrt(-1) */
    fe25519_mul(iy, h->Y, sqrtm1);     /* iy = Y*sqrt(-1) */
    fe25519_mul(eden, den1, invsqrtamd); /* eden = den1*sqrt(a-d) */

    fe25519_mul(t_z_inv, h->T, z_inv); /* t_z_inv = T*z_inv */
    rotate = fe25519_isnegative(t_z_inv);

    fe25519_copy(x_, h->X);
    fe25519_copy(y_, h->Y);
    fe25519_copy(den_inv, den2);

    fe25519_cmov(x_, iy, rotate);
    fe25519_cmov(y_, ix, rotate);
    fe25519_cmov(den_inv, eden, rotate);

    fe25519_mul(x_z_inv, x_, z_inv);
    fe25519_cneg(y_, y_, fe25519_isnegative(x_z_inv));

    fe25519_sub(s_, h->Z, y_);
    fe25519_mul(s_, den_inv, s_);
    fe25519_abs(s_, s_);
    fe25519_tobytes(s, s_);
}