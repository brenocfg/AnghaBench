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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  cf_curve25519_mul (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int*) ; 

void cf_curve25519_mul_base(u8 out[32], const u8 scalar[32])
{
  uint8_t base[32] = { 9 };
  cf_curve25519_mul(out, scalar, base);
}