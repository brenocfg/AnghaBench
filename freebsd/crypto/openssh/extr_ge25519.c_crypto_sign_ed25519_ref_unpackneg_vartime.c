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
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  t; int /*<<< orphan*/  z; } ;
typedef  TYPE_1__ ge25519_p3 ;
typedef  int /*<<< orphan*/  fe25519 ;

/* Variables and functions */
 int /*<<< orphan*/  fe25519_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fe25519_getparity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_iseq_vartime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_neg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_pow2523 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_setone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_square (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_unpack (int /*<<< orphan*/ *,unsigned char const*) ; 
 int /*<<< orphan*/  ge25519_ecd ; 
 int /*<<< orphan*/  ge25519_sqrtm1 ; 

int ge25519_unpackneg_vartime(ge25519_p3 *r, const unsigned char p[32])
{
  unsigned char par;
  fe25519 t, chk, num, den, den2, den4, den6;
  fe25519_setone(&r->z);
  par = p[31] >> 7;
  fe25519_unpack(&r->y, p); 
  fe25519_square(&num, &r->y); /* x = y^2 */
  fe25519_mul(&den, &num, &ge25519_ecd); /* den = dy^2 */
  fe25519_sub(&num, &num, &r->z); /* x = y^2-1 */
  fe25519_add(&den, &r->z, &den); /* den = dy^2+1 */

  /* Computation of sqrt(num/den) */
  /* 1.: computation of num^((p-5)/8)*den^((7p-35)/8) = (num*den^7)^((p-5)/8) */
  fe25519_square(&den2, &den);
  fe25519_square(&den4, &den2);
  fe25519_mul(&den6, &den4, &den2);
  fe25519_mul(&t, &den6, &num);
  fe25519_mul(&t, &t, &den);

  fe25519_pow2523(&t, &t);
  /* 2. computation of r->x = t * num * den^3 */
  fe25519_mul(&t, &t, &num);
  fe25519_mul(&t, &t, &den);
  fe25519_mul(&t, &t, &den);
  fe25519_mul(&r->x, &t, &den);

  /* 3. Check whether sqrt computation gave correct result, multiply by sqrt(-1) if not: */
  fe25519_square(&chk, &r->x);
  fe25519_mul(&chk, &chk, &den);
  if (!fe25519_iseq_vartime(&chk, &num))
    fe25519_mul(&r->x, &r->x, &ge25519_sqrtm1);

  /* 4. Now we have one of the two square roots, except if input was not a square */
  fe25519_square(&chk, &r->x);
  fe25519_mul(&chk, &chk, &den);
  if (!fe25519_iseq_vartime(&chk, &num))
    return -1;

  /* 5. Choose the desired square root according to parity: */
  if(fe25519_getparity(&r->x) != (1-par))
    fe25519_neg(&r->x, &r->x);

  fe25519_mul(&r->t, &r->x, &r->y);
  return 0;
}