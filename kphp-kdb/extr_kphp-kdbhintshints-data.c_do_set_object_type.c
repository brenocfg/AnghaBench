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
struct lev_hints_set_object_type {long long object_id; } ;

/* Variables and functions */
 scalar_t__ LEV_HINTS_SET_OBJECT_TYPE ; 
 struct lev_hints_set_object_type* alloc_log_event (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_object_id (long long) ; 
 int /*<<< orphan*/  check_type (int) ; 
 int set_object_type (struct lev_hints_set_object_type*) ; 

int do_set_object_type (int object_type, long long object_id, int new_object_type) {
  if (!check_type (object_type) || !check_type (new_object_type) || !check_object_id (object_id)) {
    return 0;
  }
  if (object_type == new_object_type) {
    return 1;
  }

  struct lev_hints_set_object_type *E =
    alloc_log_event (LEV_HINTS_SET_OBJECT_TYPE + 256 * object_type + new_object_type, sizeof (struct lev_hints_set_object_type), 0);

  E->object_id = object_id;

  return set_object_type (E);
}