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
typedef  int /*<<< orphan*/  user ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int user_change_order (int /*<<< orphan*/ *,int,int,int) ; 
 int user_get_aid_by_pid (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * user_get_photo_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  user_loaded (int /*<<< orphan*/ *) ; 
 scalar_t__ write_only ; 

int user_change_photo_order (user *u, int pid, int pid_near, int is_next) {
//  dbg ("user_change_photo_order %d: photo_id = %d, photo_id_near = %d, is_next = %d\n", u->id, pid, pid_near, is_next);

  if (write_only) {
    return 1;
  }

  assert (user_loaded (u));

  int aid = user_get_aid_by_pid (u, pid);
  if (aid == 0) {
    return 0;
  }

  if (pid_near != 0 && aid != user_get_aid_by_pid (u, pid_near)) {
    return 0;
  }

  data *d = user_get_photo_data (u, aid);
  if (d == NULL) {
    return 0;
  }

  return user_change_order (d, pid, pid_near, is_next) > -1;
}