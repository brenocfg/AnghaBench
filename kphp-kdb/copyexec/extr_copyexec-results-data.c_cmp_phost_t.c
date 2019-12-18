#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ first_data_time; scalar_t__ last_data_time; } ;
typedef  TYPE_1__ host_t ;

/* Variables and functions */
 int weak_cmp_phost_t (TYPE_1__ const*,TYPE_1__ const*) ; 

__attribute__((used)) static int cmp_phost_t (const void *x, const void *y) {
  const host_t *a = *(const host_t **) x, *b = *(const host_t **) y;
  int r = weak_cmp_phost_t (a, b);
  if (r) {
    return r;
  }
  if (a->first_data_time < b->first_data_time) {
    return -1;
  }
  if (a->first_data_time > b->first_data_time) {
    return 1;
  }
  if (a->last_data_time < b->last_data_time) {
    return -1;
  }
  if (a->last_data_time > b->last_data_time) {
    return 1;
  }
  return 0;
}