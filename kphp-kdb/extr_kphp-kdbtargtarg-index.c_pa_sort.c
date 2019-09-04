#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int retarget_time; } ;

/* Variables and functions */
 TYPE_1__* get_ad (int) ; 

void pa_sort (int *A, int b) {
  if (b <= 0) {
    return;
  }
  int h = get_ad (A[b >> 1])->retarget_time, i = 0, j = b;
  do {
    while (get_ad (A[i])->retarget_time < h) {
      i++;
    }
    while (get_ad (A[j])->retarget_time > h) {
      j--;
    }
    if (i <= j) {
      int t = A[i];
      A[i++] = A[j];
      A[j--] = t;
    }
  } while (i <= j);
  pa_sort (A, j);
  pa_sort (A + i, b - i);
}