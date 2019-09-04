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
typedef  int int64_t ;
typedef  int* gf ;

/* Variables and functions */

__attribute__((used)) static void unpack25519(gf o, const uint8_t *n)
{
  size_t i;
  for (i = 0; i < 16; i++)
    o[i] = n[2 * i] + ((int64_t) n[2 * i + 1] << 8);
  o[15] &= 0x7fff;
}