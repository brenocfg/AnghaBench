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
typedef  int /*<<< orphan*/ * golomb ;

/* Variables and functions */
 int LEN_BITS ; 
 scalar_t__ cur_bit ; 
 int /*<<< orphan*/  load_bit () ; 

int golomb_max_size (golomb ptr, int tot_items, int len) {
  if (ptr == NULL) {
    return 0;
  }

  int k = -1, p = 1;
  while (p < tot_items) {
    p += p;
    k++;
  }
  k = LEN_BITS;
  p = 1 << (LEN_BITS + 1);

  int m = ((int) *ptr++ << 24) + (1 << 23);

  int tmp = 0;
  while (k >= 0) {
    if (cur_bit) { tmp += (1 << k); }
    load_bit ();
    k--;
  }

  return tmp;
}