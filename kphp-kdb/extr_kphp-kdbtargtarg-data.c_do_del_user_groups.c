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
struct lev_groups_ext {int gr_num; int /*<<< orphan*/  groups; } ;
struct lev_groups {int /*<<< orphan*/  groups; } ;

/* Variables and functions */
 scalar_t__ LEV_TARG_GROUP_DEL ; 
 scalar_t__ LEV_TARG_GROUP_EXT_DEL ; 
 unsigned int MAX_USER_LEV_GROUPS ; 
 void* alloc_log_event (scalar_t__,int,int) ; 
 int del_groups (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/ * get_user (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

int do_del_user_groups (int user_id, int List[], int len) {
  user_t *U = get_user (user_id);
  if (!U || !len) {
    return 0;
  }
  if ((unsigned) len > MAX_USER_LEV_GROUPS) {
    return -1;
  }
  int i;
  for (i = 1; i < len; i++) {
    if (List[i] <= List[i-1]) {
      return -1;
    }
  }

  if (len < 256) {
    struct lev_groups *E = alloc_log_event (LEV_TARG_GROUP_DEL + len, 8 + len * 4, user_id);
    memcpy (E->groups, List, len * 4);
  } else {
    struct lev_groups_ext *E = alloc_log_event (LEV_TARG_GROUP_EXT_DEL, 12 + len * 4, user_id);
    E->gr_num = len;
    memcpy (E->groups, List, len * 4);
  }

  return del_groups (U, List, len);
}