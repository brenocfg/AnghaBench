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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/ * cf_gf128 ;

/* Variables and functions */
 int /*<<< orphan*/  write32_be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void cf_gf128_tobytes_be(const cf_gf128 in, uint8_t out[16])
{
  write32_be(in[0], out + 0);
  write32_be(in[1], out + 4);
  write32_be(in[2], out + 8);
  write32_be(in[3], out + 12);
}