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

/* Variables and functions */
 int /*<<< orphan*/  cf_curve25519_mul (int*,int const*,int*) ; 

void cf_curve25519_mul_base(uint8_t out[32], const uint8_t scalar[32])
{
  uint8_t base_point[32] = { 9 };
  cf_curve25519_mul(out, scalar, base_point);
}