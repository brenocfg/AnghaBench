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
 scalar_t__* bits_cnt_tbl ; 

void init_bits_cnt_table() {
  static int f = 0;
  if (f) {
    return;
  }
  f = 1;

  int i;
  bits_cnt_tbl[0] = 0;
  for (i = 1; i < (1 << 16); i++) {
    bits_cnt_tbl[i] = 1 + bits_cnt_tbl[i & (i - 1)];
  }
}