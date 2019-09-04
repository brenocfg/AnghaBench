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
struct TYPE_3__ {int /*<<< orphan*/  const T; int /*<<< orphan*/  const Z; int /*<<< orphan*/  const Y; int /*<<< orphan*/  const X; } ;
typedef  TYPE_1__ ge25519_p3 ;
typedef  int /*<<< orphan*/  const fe25519 ;

/* Variables and functions */
 int /*<<< orphan*/  const d ; 
 int /*<<< orphan*/  fe25519_1 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fe25519_abs (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fe25519_add (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fe25519_cmov (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  fe25519_mul (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fe25519_neg (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fe25519_sq (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fe25519_sub (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  const onemsqd ; 
 int ristretto255_sqrt_ratio_m1 (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  const sqdmone ; 
 int /*<<< orphan*/  const sqrtadm1 ; 
 int /*<<< orphan*/  const sqrtm1 ; 

__attribute__((used)) static void
ristretto255_elligator(ge25519_p3 *p, const fe25519 t)
{
    fe25519 c;
    fe25519 n;
    fe25519 one;
    fe25519 r;
    fe25519 rpd;
    fe25519 s, s_prime;
    fe25519 ss;
    fe25519 u, v;
    fe25519 w0, w1, w2, w3;
    int     wasnt_square;

    fe25519_1(one);
    fe25519_sq(r, t);                  /* r = t^2 */
    fe25519_mul(r, sqrtm1, r);         /* r = sqrt(-1)*t^2 */
    fe25519_add(u, r, one);            /* u = r+1 */
    fe25519_mul(u, u, onemsqd);        /* u = (r+1)*(1-d^2) */
    fe25519_1(c);
    fe25519_neg(c, c);                 /* c = -1 */
    fe25519_add(rpd, r, d);            /* rpd = r*d */
    fe25519_mul(v, r, d);              /* v = r*d */
    fe25519_sub(v, c, v);              /* v = c-r*d */
    fe25519_mul(v, v, rpd);            /* v = (c-r*d)*(r+d) */

    wasnt_square = 1 - ristretto255_sqrt_ratio_m1(s, u, v);
    fe25519_mul(s_prime, s, t);
    fe25519_abs(s_prime, s_prime);
    fe25519_neg(s_prime, s_prime);     /* s_prime = -|s*t| */
    fe25519_cmov(s, s_prime, wasnt_square);
    fe25519_cmov(c, r, wasnt_square);

    fe25519_sub(n, r, one);            /* n = r-1 */
    fe25519_mul(n, n, c);              /* n = c*(r-1) */
    fe25519_mul(n, n, sqdmone);        /* n = c*(r-1)*(d-1)^2 */
    fe25519_sub(n, n, v);              /* n =  c*(r-1)*(d-1)^2-v */

    fe25519_add(w0, s, s);             /* w0 = 2s */
    fe25519_mul(w0, w0, v);            /* w0 = 2s*v */
    fe25519_mul(w1, n, sqrtadm1);      /* w1 = n*sqrt(ad-1) */
    fe25519_sq(ss, s);                 /* ss = s^2 */
    fe25519_sub(w2, one, ss);          /* w2 = 1-s^2 */
    fe25519_add(w3, one, ss);          /* w3 = 1+s^2 */

    fe25519_mul(p->X, w0, w3);
    fe25519_mul(p->Y, w2, w1);
    fe25519_mul(p->Z, w1, w3);
    fe25519_mul(p->T, w0, w2);
}