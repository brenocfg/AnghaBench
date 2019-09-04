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
typedef  int limb ;

/* Variables and functions */

__attribute__((used)) static void freduce_degree(limb *output) {
  /* Each of these shifts and adds ends up multiplying the value by 19.
   *
   * For output[0..8], the absolute entry value is < 14*2^54 and we add, at
   * most, 19*14*2^54 thus, on exit, |output[0..8]| < 280*2^54. */
  output[8] += output[18] << 4;
  output[8] += output[18] << 1;
  output[8] += output[18];
  output[7] += output[17] << 4;
  output[7] += output[17] << 1;
  output[7] += output[17];
  output[6] += output[16] << 4;
  output[6] += output[16] << 1;
  output[6] += output[16];
  output[5] += output[15] << 4;
  output[5] += output[15] << 1;
  output[5] += output[15];
  output[4] += output[14] << 4;
  output[4] += output[14] << 1;
  output[4] += output[14];
  output[3] += output[13] << 4;
  output[3] += output[13] << 1;
  output[3] += output[13];
  output[2] += output[12] << 4;
  output[2] += output[12] << 1;
  output[2] += output[12];
  output[1] += output[11] << 4;
  output[1] += output[11] << 1;
  output[1] += output[11];
  output[0] += output[10] << 4;
  output[0] += output[10] << 1;
  output[0] += output[10];
}