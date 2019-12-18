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
struct lev_hints_set_object_type {int type; scalar_t__ object_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  changes_count ; 
 int /*<<< orphan*/  check_object_id (scalar_t__) ; 
 int /*<<< orphan*/  chg_list_add_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  global_changes_en ; 
 int /*<<< orphan*/  global_changes_st ; 
 scalar_t__ no_changes ; 
 int /*<<< orphan*/ ** stat_global ; 
 scalar_t__ write_only ; 

int set_object_type (struct lev_hints_set_object_type *E) {
  int object_type = (E->type >> 8) & 255;
  int new_object_type = E->type & 255;
  if (!check_object_id (E->object_id) || object_type == 0 || new_object_type == 0) {
    return 0;
  }

  if (write_only || no_changes || object_type == new_object_type) {
    return 1;
  }

  stat_global[object_type][2]++;

  chg_list_add_int (&global_changes_st, &global_changes_en, object_type + 256, (int)E->object_id, new_object_type);
  changes_count++;

  return 1;
}