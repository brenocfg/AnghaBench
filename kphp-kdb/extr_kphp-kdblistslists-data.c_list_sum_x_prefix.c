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
 scalar_t__ Sum ; 
 scalar_t__ __have_weights ; 
 int object_id_compare_prefix (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int object_id_ints_adjusted ; 

__attribute__((used)) static inline int list_sum_x_prefix (object_id_t x) {
  int p;
  while (IF_LISTS_Z(LA < LE) && (p = object_id_compare_prefix (OARR_ENTRY (LA, 0), x)) < 0) {
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
    //LA += object_id_ints_adjusted;
    Sum += __have_weights ? LA[object_id_ints_adjusted-1] : 1;
  }
  return 0;
}