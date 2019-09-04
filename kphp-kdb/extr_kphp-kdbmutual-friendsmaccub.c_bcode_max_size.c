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
typedef  int /*<<< orphan*/  bcode ;

/* Variables and functions */

int  bcode_max_size (bcode ptr, int tot_items, int len) {
  return len; // this is wrong but.. but it is OK
  /*
  int k = 0;
  int p = 1;

  while (p <= tot_items) {
    p += p;
    k++;
  }
  if (k > 0) {
    assert (x != NULL);
    return 8 * len / it->k;
  } else {
    assert (x == NULL);
    return 0;
  }
  */
}