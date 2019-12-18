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
 scalar_t__ GET_MAX_PHOTOS (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ data_get_cnt (int /*<<< orphan*/ *) ; 
 scalar_t__ data_get_hidden_state (int /*<<< orphan*/ *,int) ; 
 int data_restore (int /*<<< orphan*/ *,int) ; 
 int user_get_aid_by_pid (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * user_get_photo_data (int /*<<< orphan*/ *,int) ; 
 scalar_t__ write_only ; 

int user_restore_photo (user *u, int pid) {
  if (write_only) {
    return 1;
  }

  int aid = user_get_aid_by_pid (u, pid);
  if (aid == 0) {
    return 0;
  }
  data *d = user_get_photo_data (u, aid);
  if (d == NULL) {
    return 0;
  }
  if (data_get_hidden_state (d, pid) == 0) {
    return 0;
  }
  if (data_get_cnt (d) >= GET_MAX_PHOTOS (aid)) {
    return 0;
  }
  assert (data_restore (d, pid) > -1);
  return 1;
}