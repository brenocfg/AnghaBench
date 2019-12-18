#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int id; int local_id; int /*<<< orphan*/  d; int /*<<< orphan*/  current_album_id; int /*<<< orphan*/  current_photo_id; } ;
typedef  TYPE_2__ user ;
struct TYPE_8__ {int user_cnt; TYPE_1__* user_index; } ;
struct TYPE_6__ {int id; int /*<<< orphan*/  current_album_id; int /*<<< orphan*/  current_photo_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIN_NEW_ALBUM_ID ; 
 int /*<<< orphan*/  MIN_NEW_PHOTO_ID ; 
 int /*<<< orphan*/  album_func ; 
 int /*<<< orphan*/  assert (int) ; 
 int cur_local_id ; 
 int /*<<< orphan*/  data_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dl_abs (int) ; 
 int /*<<< orphan*/  h_users ; 
 TYPE_4__ header ; 
 scalar_t__ import_dump_mode ; 
 int log_split_min ; 
 int log_split_mod ; 
 scalar_t__ set_intp_add (int /*<<< orphan*/ *,int*) ; 
 int user_cnt ; 
 TYPE_2__* users ; 
 int /*<<< orphan*/  write_only ; 

user *conv_uid (int user_id) {
  if (user_id == 0) {
    return NULL;
  }
  if (dl_abs (user_id) % log_split_mod != log_split_min) {
    return NULL;
  }
  if (import_dump_mode) {
    return users;
  }

  user **u = (user **)set_intp_add (&h_users, &user_id);
  if (*u == (user *)&user_id) {
    assert (cur_local_id + 1 < user_cnt);

    *u = &users[++cur_local_id];
    (*u)->id = user_id;
    (*u)->local_id = cur_local_id;

    if (cur_local_id <= header.user_cnt) {
      assert (user_id == header.user_index[cur_local_id].id);
      (*u)->current_photo_id = header.user_index[cur_local_id].current_photo_id;
      (*u)->current_album_id = header.user_index[cur_local_id].current_album_id;
    } else {
      (*u)->current_photo_id = MIN_NEW_PHOTO_ID;
      (*u)->current_album_id = MIN_NEW_ALBUM_ID;
    }
//    dbg ("ID = %d, current_album_id = %d\n", user_id, (*u)->current_album_id);

    if (!write_only) {
      data_init (&(*u)->d, &album_func);
    }
  }
  return *u;
}