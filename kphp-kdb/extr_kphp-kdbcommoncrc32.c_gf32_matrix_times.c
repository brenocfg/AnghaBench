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

__attribute__((used)) static unsigned gf32_matrix_times (unsigned *matrix, unsigned vector) {
  unsigned sum = 0;
  while (vector) {
    if (vector & 1) {
      sum ^= *matrix;
    }
    vector >>= 1;
    matrix++;
  }
  return sum;
}