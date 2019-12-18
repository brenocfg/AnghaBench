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
struct TYPE_2__ {int /*<<< orphan*/  object_table; } ;

/* Variables and functions */
 TYPE_1__* __u ; 
 long long ltbl_get_rev (int /*<<< orphan*/ *,int) ; 

int cmp_obj (const void * _a, const void * _b) {
  int x = *(int *)_a, y = *(int *)_b;
  long long a = ltbl_get_rev (&__u->object_table, x), b = ltbl_get_rev (&__u->object_table, y);
  if (a < b) {
    return -1;
  } else if (a > b) {
    return +1;
  }
  return 0;
}