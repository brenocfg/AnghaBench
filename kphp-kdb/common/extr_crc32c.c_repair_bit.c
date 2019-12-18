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

__attribute__((used)) static int repair_bit (unsigned char *input, int l, int k) {
  if (k < 0) {
    return -1;
  }
  int idx = k >> 5, bit = k & 31, i = (l - 1) - (idx - 1) * 4;
  while (bit >= 8) {
    i--;
    bit -= 8;
  }
  if (i < 0) {
    return -2;
  }
  if (i >= l) {
    return -3;
  }
  int j = 7 - bit;
  input[i] ^= 1 << j;
  return 0;
}