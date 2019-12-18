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
 int* zzmalloc0 (int) ; 

__attribute__((used)) static inline int cnt_incr (int **p, int s, int t) {
  if (s > 0 && s <= t) {
    if (!*p) { *p = zzmalloc0 (t * sizeof(int)); }
    (*p)[s-1]++;
    return s;
  } else {
    return 0;
  }
}