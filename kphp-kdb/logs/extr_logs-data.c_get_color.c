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
 int FN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * color_int ; 
 int /*<<< orphan*/ * color_ll ; 
 int* map_int_int_get (int /*<<< orphan*/ *,long long) ; 
 int* map_ll_int_get (int /*<<< orphan*/ *,long long) ; 
 scalar_t__* std_t ; 

int get_color (int field_num, long long field_value) {
  assert (0 <= field_num && field_num < FN);

  if (std_t[field_num]) {
    int *t = map_ll_int_get (&color_ll[field_num], field_value);
    if (t != NULL) {
      return *t;
    }
  } else {
    int *t = map_int_int_get (&color_int[field_num], field_value);
    if (t != NULL) {
      return *t;
    }
  }

  return 0;
}