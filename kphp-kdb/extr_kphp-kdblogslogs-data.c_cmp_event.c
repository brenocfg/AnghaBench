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
 long long* global_data ; 
 int global_rcid ; 
 int global_sort_direction ; 
 int global_sort_field ; 
 scalar_t__ global_sort_type ; 
 scalar_t__ t_double ; 

int cmp_event (const void *a, const void *b) {
  int i1 = *(int *)a, i2 = *(int *)b;

  if (global_sort_type == t_double) {
    double val1 = *(double *)&global_data[i1 + global_rcid * global_sort_field],
           val2 = *(double *)&global_data[i2 + global_rcid * global_sort_field];
    if (val1 != val2) {
      return (2 * (val1 > val2) - 1) * global_sort_direction;
    }
    if (i1 != i2) {
      return (2 * (i1 > i2) - 1) * global_sort_direction;
    }
    return 0;
  }
  long long val1 = global_data[i1 + global_rcid * global_sort_field],
            val2 = global_data[i2 + global_rcid * global_sort_field];
  if (val1 != val2) {
    return (2 * (val1 > val2) - 1) * global_sort_direction;
  }
  if (i1 != i2) {
    return (2 * (i1 > i2) - 1) * global_sort_direction;
  }
  return 0;
}