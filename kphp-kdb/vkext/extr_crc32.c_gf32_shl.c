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

/* Variables and functions */
 int gf32_mod (unsigned long long,int) ; 

__attribute__((used)) static unsigned gf32_shl (unsigned int a, int shift) {
  unsigned long long r = a;
  r <<= shift;
  return gf32_mod (r, 31 + shift);
}