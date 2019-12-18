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

__attribute__((used)) static inline unsigned gf32_mod (unsigned long long r, int high_bit) {
  int j = high_bit;
  for (j = high_bit; j >= 32; j--) {
    if ((1ULL << j) & r) {
      r ^= 0x1EDC6F41ULL << (j - 32);
    }
  }
  return (unsigned) r;
}