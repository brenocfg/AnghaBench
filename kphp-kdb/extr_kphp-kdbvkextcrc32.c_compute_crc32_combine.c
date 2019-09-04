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
 int /*<<< orphan*/  gf32_matrix_square (unsigned int*,unsigned int*) ; 
 unsigned int gf32_matrix_times (unsigned int*,unsigned int) ; 

unsigned compute_crc32_combine (unsigned crc1, unsigned crc2, int len2) {
  static int power_buf_initialized = 0;
  static unsigned power_buf[1024];
  int n;
  /* degenerate case (also disallow negative lengths) */
  if (len2 <= 0) {
    return crc1;
  }
  if (!power_buf_initialized) {
    power_buf[0] = 0xedb88320UL;
    for (n = 0; n < 31; n++) {
      power_buf[n+1] = 1U << n;
    }
    for (n = 1; n < 32; n++) {
      gf32_matrix_square (power_buf + (n << 5), power_buf + ((n - 1) << 5));
    }
    power_buf_initialized = 1;
  }

  unsigned int *p = power_buf + 64;
  do {
    p += 32;
    if (len2 & 1) {
      crc1 = gf32_matrix_times (p, crc1);
    }
    len2 >>= 1;
  } while (len2);
  return crc1 ^ crc2;
}