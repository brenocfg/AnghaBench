#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int date; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 TYPE_1__** H ; 
 int HN ; 

__attribute__((used)) static void aux_heap_sort (void) {
  int i, j, k, r;
  if (!HN) { return; }
  for (k = HN - 1; k > 0; k--) {
    tree_t *t = H[k+1];
    H[k+1] = H[1];
    r = t->date;
    i = 1;
    while (1) {
      j = 2*i;
      if (j > k) { break; }
      if (j < k && H[j+1]->date < H[j]->date) { j++; }
      if (r <= H[j]->date) { break; }
      H[i] = H[j];
      i = j;
    }
    H[i] = t;
  }
  for (i = 0; i < HN; i++) {
    H[i] = H[i+1];
  }
}