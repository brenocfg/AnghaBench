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
 int min (int,int) ; 

int key_cmp2 (int l1, const int *k1, int l2, const int *k2, int s) {
  int i;
  int l = min (l1, l2);
  for (i = s; i < l; i++) {
    if (k1[i] < k2[i]) {
      return -(i + 1);
    } else if (k1[i] > k2[i]) {
      return (i + 1);
    }
  }
  if (l1 < l2) {
    return -(i + 1);
  } else if (l1 > l2) {
    return (i + 1);
  } else {
    return 0;
  }
}