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

/* Variables and functions */
 unsigned int MAX_USER_LEV_GROUPS ; 
 int do_add_user_groups (int,int*,int) ; 
 int do_delete_groups (int) ; 
 int /*<<< orphan*/ * get_user (int) ; 

int do_set_user_groups (int user_id, int List[], int len) {
  user_t *U = get_user (user_id);
  if (!U) {
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

  if (!len) {
    return do_delete_groups (user_id);
  }
  do_delete_groups (user_id);
  
  return do_add_user_groups (user_id, List, len);
}