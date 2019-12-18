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
typedef  scalar_t__ hash_t ;

/* Variables and functions */
 scalar_t__* Q ; 

void hsort (int a, int b) {
  int i, j;
  hash_t h, t;
  if (a >= b) return;
  i = a;
  j = b;
  h = Q[(a+b) >> 1];
  do {
    while (Q[i] < h) i++;
    while (Q[j] > h) j--;
    if (i <= j) {
      t = Q[i];  Q[i++] = Q[j];  Q[j--] = t;
    }
  } while (i <= j);
  hsort (a, j);
  hsort (i, b);
}