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
typedef  int /*<<< orphan*/  user_t ;
struct lev_groups {int* groups; } ;

/* Variables and functions */
 scalar_t__ LEV_TARG_GROUP_ADD ; 
 int add_groups (int /*<<< orphan*/ *,int*,int) ; 
 struct lev_groups* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/ * get_user (int) ; 

int do_set_user_group (int user_id, int group_id) {
  user_t *U = get_user (user_id);
  if (!U) {
    return 0;
  }

  struct lev_groups *E = alloc_log_event (LEV_TARG_GROUP_ADD + 1, 12, user_id);
  E->groups[0] = group_id;

  return add_groups (U, E->groups, 1);
}