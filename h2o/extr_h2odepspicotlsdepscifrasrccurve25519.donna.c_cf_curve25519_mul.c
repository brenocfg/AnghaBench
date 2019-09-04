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
typedef  int uint8_t ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  limb ;

/* Variables and functions */
 int /*<<< orphan*/  cmult (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crecip (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fcontract (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fexpand (int /*<<< orphan*/ *,int const*) ; 
 int /*<<< orphan*/  fmul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void cf_curve25519_mul(u8 out[32], const u8 scalar[32], const u8 point[32])
{
  limb bp[10], x[10], z[11], zmone[10];
  uint8_t e[32];
  int i;

  for (i = 0; i < 32; ++i) e[i] = scalar[i];
  e[0] &= 248;
  e[31] &= 127;
  e[31] |= 64;

  fexpand(bp, point);
  cmult(x, z, e, bp);
  crecip(zmone, z);
  fmul(z, x, zmone);
  fcontract(out, z);
}