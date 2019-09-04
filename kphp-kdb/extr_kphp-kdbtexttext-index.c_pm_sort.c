#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {long long freq; } ;
typedef  TYPE_1__ word_t ;
struct TYPE_5__ {TYPE_1__* w; } ;
typedef  TYPE_2__ pm_cell_t ;

/* Variables and functions */

void pm_sort (pm_cell_t *A, int b) {
  int i = 0, j = b;
  word_t *t;
  long long h;
  if (b <= 0) { return; }
  h = A[b >> 1].w->freq;
  do {
    while (A[i].w->freq < h) { i++; }
    while (A[j].w->freq > h) { j--; }
    if (i <= j) {
      t = A[i].w;  A[i++].w = A[j].w;  A[j--].w = t;
    }
  } while (i <= j);
  pm_sort (A+i, b-i);
  pm_sort (A, j);
}