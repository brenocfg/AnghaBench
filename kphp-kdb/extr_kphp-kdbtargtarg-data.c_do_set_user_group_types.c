#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  user_group_types; } ;
typedef  TYPE_1__ user_t ;
struct lev_targ_user_group_types {int /*<<< orphan*/  user_group_types; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_TARG_USER_GROUP_TYPES ; 
 scalar_t__ alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* get_user (int) ; 
 int /*<<< orphan*/  memcmp (unsigned int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned int*,int) ; 
 int set_user_group_types (struct lev_targ_user_group_types*) ; 

int do_set_user_group_types (int user_id, unsigned user_group_types[4]) {
  user_t *U = get_user (user_id);
  if (!U) {
    return 0;
  }
  if (!memcmp (user_group_types, U->user_group_types, 16)) {
    return 1;
  }
  struct lev_targ_user_group_types *E = (struct lev_targ_user_group_types *) alloc_log_event (LEV_TARG_USER_GROUP_TYPES, 24, user_id);
  memcpy (E->user_group_types, user_group_types, 16);
  return set_user_group_types (E);
}