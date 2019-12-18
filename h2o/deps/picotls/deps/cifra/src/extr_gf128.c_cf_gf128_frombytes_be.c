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
 int /*<<< orphan*/  read32_be (int /*<<< orphan*/  const*) ; 

void cf_gf128_frombytes_be(const uint8_t in[16], cf_gf128 out)
{
  out[0] = read32_be(in + 0);
  out[1] = read32_be(in + 4);
  out[2] = read32_be(in + 8);
  out[3] = read32_be(in + 12);
}