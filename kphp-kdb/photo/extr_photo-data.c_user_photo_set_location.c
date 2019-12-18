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
typedef  int /*<<< orphan*/  user ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {int v_raw_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMP_ADD_CHANGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  photo_type__location ; 
 int /*<<< orphan*/  photo_type__original_location ; 
 int /*<<< orphan*/  raw ; 
 TYPE_1__* tmp_field_changes ; 
 size_t tmp_field_changes_n ; 
 int /*<<< orphan*/  user_change_data (int /*<<< orphan*/ *,int,TYPE_1__*,size_t,int) ; 
 int user_get_aid_by_pid (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * user_get_photo_data (int /*<<< orphan*/ *,int) ; 
 scalar_t__ user_loaded (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_only ; 

int user_photo_set_location (user *u, int pid, int original, char *loc, int len) {
//  dbg ("user_photo_set_location %d: photo_id = %d, len = %d\n", u->id, pid, len);

  assert (user_loaded (u) && !write_only);

  int aid = user_get_aid_by_pid (u, pid);
  assert (aid != 0);

  data *d = user_get_photo_data (u, aid);
  if (d == NULL) {
    return 0;
  }

  tmp_field_changes_n = 0;
  tmp_field_changes[tmp_field_changes_n].v_raw_len = len;
  TMP_ADD_CHANGE (original ? photo_type__original_location : photo_type__location, raw, loc);

  user_change_data (d, pid, tmp_field_changes, tmp_field_changes_n, 1);

  return 1;
}