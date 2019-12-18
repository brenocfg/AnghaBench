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
struct iterator {int x; } ;

/* Variables and functions */

__attribute__((used)) static inline void it_heap_insert (struct iterator **H, int HN, struct iterator *cur) {
  int i = ++HN, j, x = cur->x;
  while (i > 1) {
    j = (i >> 1);
    if (H[j]->x >= x) {
      break;
    }
    H[i] = H[j];
    i = j;
  }
  H[i] = cur;
}