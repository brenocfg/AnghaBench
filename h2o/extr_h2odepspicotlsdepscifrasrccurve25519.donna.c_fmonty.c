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
typedef  int /*<<< orphan*/  const limb ;

/* Variables and functions */
 int /*<<< orphan*/  fdifference (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fproduct (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  freduce_coefficients (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  freduce_degree (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fscalar_product (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  fsquare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fsum (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fmonty(limb *x2, limb *z2,  /* output 2Q */
                   limb *x3, limb *z3,  /* output Q + Q' */
                   limb *x, limb *z,    /* input Q */
                   limb *xprime, limb *zprime,  /* input Q' */
                   const limb *qmqp /* input Q - Q' */) {
  limb origx[10], origxprime[10], zzz[19], xx[19], zz[19], xxprime[19],
        zzprime[19], zzzprime[19], xxxprime[19];

  memcpy(origx, x, 10 * sizeof(limb));
  fsum(x, z);
  /* |x[i]| < 2^27 */
  fdifference(z, origx);  /* does x - z */
  /* |z[i]| < 2^27 */

  memcpy(origxprime, xprime, sizeof(limb) * 10);
  fsum(xprime, zprime);
  /* |xprime[i]| < 2^27 */
  fdifference(zprime, origxprime);
  /* |zprime[i]| < 2^27 */
  fproduct(xxprime, xprime, z);
  /* |xxprime[i]| < 14*2^54: the largest product of two limbs will be <
   * 2^(27+27) and fproduct adds together, at most, 14 of those products.
   * (Approximating that to 2^58 doesn't work out.) */
  fproduct(zzprime, x, zprime);
  /* |zzprime[i]| < 14*2^54 */
  freduce_degree(xxprime);
  freduce_coefficients(xxprime);
  /* |xxprime[i]| < 2^26 */
  freduce_degree(zzprime);
  freduce_coefficients(zzprime);
  /* |zzprime[i]| < 2^26 */
  memcpy(origxprime, xxprime, sizeof(limb) * 10);
  fsum(xxprime, zzprime);
  /* |xxprime[i]| < 2^27 */
  fdifference(zzprime, origxprime);
  /* |zzprime[i]| < 2^27 */
  fsquare(xxxprime, xxprime);
  /* |xxxprime[i]| < 2^26 */
  fsquare(zzzprime, zzprime);
  /* |zzzprime[i]| < 2^26 */
  fproduct(zzprime, zzzprime, qmqp);
  /* |zzprime[i]| < 14*2^52 */
  freduce_degree(zzprime);
  freduce_coefficients(zzprime);
  /* |zzprime[i]| < 2^26 */
  memcpy(x3, xxxprime, sizeof(limb) * 10);
  memcpy(z3, zzprime, sizeof(limb) * 10);

  fsquare(xx, x);
  /* |xx[i]| < 2^26 */
  fsquare(zz, z);
  /* |zz[i]| < 2^26 */
  fproduct(x2, xx, zz);
  /* |x2[i]| < 14*2^52 */
  freduce_degree(x2);
  freduce_coefficients(x2);
  /* |x2[i]| < 2^26 */
  fdifference(zz, xx);  // does zz = xx - zz
  /* |zz[i]| < 2^27 */
  memset(zzz + 10, 0, sizeof(limb) * 9);
  fscalar_product(zzz, zz, 121665);
  /* |zzz[i]| < 2^(27+17) */
  /* No need to call freduce_degree here:
     fscalar_product doesn't increase the degree of its input. */
  freduce_coefficients(zzz);
  /* |zzz[i]| < 2^26 */
  fsum(zzz, xx);
  /* |zzz[i]| < 2^27 */
  fproduct(z2, zz, zzz);
  /* |z2[i]| < 14*2^(26+27) */
  freduce_degree(z2);
  freduce_coefficients(z2);
  /* |z2|i| < 2^26 */
}