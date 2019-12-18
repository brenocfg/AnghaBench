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

/* Variables and functions */
 scalar_t__ LEV_FR_DEL_CAT ; 
 int /*<<< orphan*/  alloc_log_event (scalar_t__,int,int) ; 
 scalar_t__ conv_uid (int) ; 
 int delete_friend_category (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  get_user (int) ; 

int do_delete_friend_category (int user_id, int cat) {
  if (conv_uid (user_id) < 0 || cat <= 0 || cat > 30) {
    return -1;
  }
  alloc_log_event (LEV_FR_DEL_CAT+cat, 8, user_id);

  return delete_friend_category (get_user (user_id), cat, 1);
}