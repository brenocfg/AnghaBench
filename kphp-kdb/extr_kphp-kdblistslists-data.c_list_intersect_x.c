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

/* Variables and functions */
 scalar_t__ IF_LISTS_Z (int) ; 
 scalar_t__* LA ; 
 scalar_t__* LE ; 
 scalar_t__ MAX_OBJECT_ID ; 
 int /*<<< orphan*/  OARR_ENTRY (scalar_t__*,int /*<<< orphan*/ ) ; 
 int object_id_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_id_ints_adjusted ; 
 int /*<<< orphan*/  store_object_id_intersect_v (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int list_intersect_x (object_id_t x) {
  int p;
  while (IF_LISTS_Z(LA < LE) && (p = object_id_compare (OARR_ENTRY (LA, 0), x)) < 0) {
    LA += object_id_ints_adjusted;
  }

  #ifdef LISTS_Z
  if (LA >= LE) {
    return 0;
  }
  #else
  if (*LA == MAX_OBJECT_ID) {
    return 0;
  }
  #endif
  if (!p) {
    store_object_id_intersect_v (OARR_ENTRY (LA, 0));
    LA += object_id_ints_adjusted;
  }
  return 0;
}