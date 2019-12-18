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
 int CAT_FR_ALL ; 
 int CAT_FR_FR ; 
 int* P ; 
 int PL ; 
 int PL_M_CAT ; 
 int PL_M_MASK ; 

__attribute__((used)) static int remove_unused_cats (void) {
  int *A = P, *B = P, x, m = 0, m1 = 0;
  while (*A != -1 && m1 != CAT_FR_ALL) {
    x = *A++;
    if (x & PL_M_CAT) {
      x &= PL_M_MASK;
      if (x == CAT_FR_ALL || x == CAT_FR_FR) {
        if (m1 >= x) {
          continue;
        }
        m1 |= x;
        m = -1;
      } else {
        x = (1 << (x & 0x1f));
        if (m & x) {
          continue;
        }
        if (x == 1) {
          x = -1;
        }
        m |= x;
      }
      x = A[-1];
    }
    *B++ = x;
  }
  *B = -1;
  PL = B - A;
  return PL;
}