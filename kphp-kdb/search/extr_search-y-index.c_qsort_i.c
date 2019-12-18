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
struct item {long long item_id; } ;

/* Variables and functions */
 struct item** Items ; 

__attribute__((used)) static void qsort_i (int a, int b) {
  int i, j;
  long long h;
  struct item *t;
  if (a >= b) { return; }
  h = Items[(a+b)>>1]->item_id;
  i = a;
  j = b;
  do {
    while (Items[i]->item_id < h) { i++; }
    while (Items[j]->item_id > h) { j--; }
    if (i <= j) {
      t = Items[i];  Items[i++] = Items[j];  Items[j--] = t;
    }
  } while (i <= j);
  qsort_i (a, j);
  qsort_i (i, b);
}