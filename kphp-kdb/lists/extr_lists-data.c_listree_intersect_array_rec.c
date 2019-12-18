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
typedef  int /*<<< orphan*/  object_id_t ;
typedef  int /*<<< orphan*/  listree_t ;

/* Variables and functions */
 int /*<<< orphan*/  LA ; 
 int /*<<< orphan*/  OARR_ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_array (int /*<<< orphan*/ *,int) ; 
 scalar_t__ object_id_less (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_x (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void listree_intersect_array_rec (listree_t *LT, int a, int b, object_id_t upper_bound) {
  if (a > b) {
    return;
  }
  int m = (a + b) >> 1;
  object_id_t x = get_array (LT, m);
  if (object_id_less (OARR_ENTRY (LA, 0), x)) {
    listree_intersect_array_rec (LT, a, m - 1, x);
  }
  report_x (x);
  if (object_id_less (OARR_ENTRY (LA, 0), upper_bound)) {
    listree_intersect_array_rec (LT, m + 1, b, upper_bound);
  }
}