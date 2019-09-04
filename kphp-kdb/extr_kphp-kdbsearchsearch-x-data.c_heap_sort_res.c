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
struct item {int dummy; } ;

/* Variables and functions */
 struct item** R ; 
 double* RR ; 
 int R_cnt ; 

__attribute__((used)) static void heap_sort_res (void) {
  int i, j, k;
  struct item *t;
  for (k = R_cnt - 1; k > 0; k--) {
    t = R[k+1];
    double r = RR[k+1];
    R[k+1] = R[1];
    RR[k+1] = RR[1];
    i = 1;
    while (1) {
      j = 2*i;
      if (j > k) { break; }
      if (j < k) {
        if (RR[j+1] > RR[j]) { j++; }
      }
      if (r >= RR[j]) { break; }
      R[i] = R[j];
      RR[i] = RR[j];
      i = j;
    }
    R[i] = t;
    RR[i] = r;
  }

  for (i = 0; i < R_cnt; i++) {
    R[i] = R[i+1];
    RR[i] = RR[i+1];
  }
}