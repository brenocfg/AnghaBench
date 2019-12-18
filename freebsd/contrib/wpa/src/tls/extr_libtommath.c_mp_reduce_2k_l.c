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
typedef  int /*<<< orphan*/  mp_int ;

/* Variables and functions */
 scalar_t__ MP_LT ; 
 int MP_OKAY ; 
 int /*<<< orphan*/  mp_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ mp_cmp_mag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mp_count_bits (int /*<<< orphan*/ *) ; 
 int mp_div_2d (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mp_init (int /*<<< orphan*/ *) ; 
 int mp_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int s_mp_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_mp_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mp_reduce_2k_l(mp_int *a, mp_int *n, mp_int *d)
{
   mp_int q;
   int    p, res;

   if ((res = mp_init(&q)) != MP_OKAY) {
      return res;
   }

   p = mp_count_bits(n);
top:
   /* q = a/2**p, a = a mod 2**p */
   if ((res = mp_div_2d(a, p, &q, a)) != MP_OKAY) {
      goto ERR;
   }

   /* q = q * d */
   if ((res = mp_mul(&q, d, &q)) != MP_OKAY) {
      goto ERR;
   }

   /* a = a + q */
   if ((res = s_mp_add(a, &q, a)) != MP_OKAY) {
      goto ERR;
   }

   if (mp_cmp_mag(a, n) != MP_LT) {
      s_mp_sub(a, n, a);
      goto top;
   }

ERR:
   mp_clear(&q);
   return res;
}