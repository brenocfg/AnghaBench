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

__attribute__((used)) static int xor_hcyf (int a, int b) {
  if (a >= 'A') { a -= 7; }
  if (b >= 'B') { b -= 7; }
  a = (a ^ b) & 15;
  return a < 10 ? '0' + a : '0' + 0x27 + a;
}