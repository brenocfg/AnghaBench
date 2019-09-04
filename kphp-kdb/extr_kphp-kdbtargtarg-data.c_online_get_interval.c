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
 scalar_t__ OLIST_COUNT ; 
 scalar_t__* ocntT ; 

__attribute__((used)) static inline int online_get_interval (int l, int r) {
  l += OLIST_COUNT;
  r += OLIST_COUNT;

  int res = 0;

  while (l <= r) {
    if (l & 1) {
      res += ocntT[l++];
    }
    if (!(r & 1)) {
      res += ocntT[r--];
    }
    l >>= 1;
    r >>= 1;
  }

  return res;
}