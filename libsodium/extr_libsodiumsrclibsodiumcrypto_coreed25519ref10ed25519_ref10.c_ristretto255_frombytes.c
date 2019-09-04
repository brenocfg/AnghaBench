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
struct TYPE_3__ {int /*<<< orphan*/  Y; int /*<<< orphan*/  T; int /*<<< orphan*/  X; int /*<<< orphan*/  Z; } ;
typedef  TYPE_1__ ge25519_p3 ;
typedef  int /*<<< orphan*/  fe25519 ;

/* Variables and functions */
 int /*<<< orphan*/  d ; 
 int /*<<< orphan*/  fe25519_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_frombytes (int /*<<< orphan*/ ,unsigned char const*) ; 
 int fe25519_isnegative (int /*<<< orphan*/ ) ; 
 int fe25519_iszero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_neg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_sq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ristretto255_is_canonical (unsigned char const*) ; 
 int ristretto255_sqrt_ratio_m1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ristretto255_frombytes(ge25519_p3 *h, const unsigned char *s)
{
    fe25519 inv_sqrt;
    fe25519 one;
    fe25519 s_;
    fe25519 ss;
    fe25519 u1, u2;
    fe25519 u1u1, u2u2;
    fe25519 v;
    fe25519 v_u2u2;
    int     was_square;

    if (ristretto255_is_canonical(s) == 0) {
        return -1;
    }
    fe25519_frombytes(s_, s);
    fe25519_sq(ss, s_);                /* ss = s^2 */

    fe25519_1(u1);
    fe25519_sub(u1, u1, ss);           /* u1 = 1-ss */
    fe25519_sq(u1u1, u1);              /* u1u1 = u1^2 */

    fe25519_1(u2);
    fe25519_add(u2, u2, ss);           /* u2 = 1+ss */
    fe25519_sq(u2u2, u2);              /* u2u2 = u2^2 */

    fe25519_mul(v, d, u1u1);           /* v = d*u1^2 */
    fe25519_neg(v, v);                 /* v = -d*u1^2 */
    fe25519_sub(v, v, u2u2);           /* v = -(d*u1^2)-u2^2 */

    fe25519_mul(v_u2u2, v, u2u2);      /* v_u2u2 = v*u2^2 */

    fe25519_1(one);
    was_square = ristretto255_sqrt_ratio_m1(inv_sqrt, one, v_u2u2);
    fe25519_mul(h->X, inv_sqrt, u2);
    fe25519_mul(h->Y, inv_sqrt, h->X);
    fe25519_mul(h->Y, h->Y, v);

    fe25519_mul(h->X, h->X, s_);
    fe25519_add(h->X, h->X, h->X);
    fe25519_abs(h->X, h->X);
    fe25519_mul(h->Y, u1, h->Y);
    fe25519_1(h->Z);
    fe25519_mul(h->T, h->X, h->Y);

    return - ((1 - was_square) |
              fe25519_isnegative(h->T) | fe25519_iszero(h->Y));
}