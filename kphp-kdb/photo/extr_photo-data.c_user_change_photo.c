#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int id; int /*<<< orphan*/  album_by_photo; } ;
typedef  TYPE_1__ user ;
struct TYPE_14__ {int /*<<< orphan*/ * e; int /*<<< orphan*/  tp; } ;
typedef  TYPE_2__ my_change ;
struct TYPE_15__ {scalar_t__ v_fid; int v_int; } ;
typedef  TYPE_3__ field ;
typedef  int /*<<< orphan*/  event ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  change ;
struct TYPE_16__ {int /*<<< orphan*/ * obj; int /*<<< orphan*/  dyn; } ;
typedef  TYPE_4__ actual_object ;

/* Variables and functions */
 scalar_t__ GET_MAX_PHOTOS (int) ; 
 int /*<<< orphan*/  PHOTO_TYPE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ch_event ; 
 int /*<<< orphan*/  check_album_id (int) ; 
 int /*<<< orphan*/  data_add_change (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int data_add_object (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  data_del (int /*<<< orphan*/ *,int) ; 
 scalar_t__ data_get_actual_object (int /*<<< orphan*/ *,int,TYPE_4__*) ; 
 scalar_t__ data_get_cnt (int /*<<< orphan*/ *) ; 
 scalar_t__ data_get_hidden_state (int /*<<< orphan*/ *,int) ; 
 int data_get_local_id_by_id (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dbg (char*,int,int,int) ; 
 int /*<<< orphan*/ * event_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * event_update_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_set (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ photo_type_album_id ; 
 scalar_t__ photo_type_id ; 
 scalar_t__ photo_type_owner_id ; 
 int user_change_data (int /*<<< orphan*/ *,int,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_create_album_force (TYPE_1__*,int) ; 
 int user_get_aid_by_pid (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * user_get_photo_data (TYPE_1__*,int) ; 
 int user_loaded (TYPE_1__*) ; 
 scalar_t__ write_only ; 

int user_change_photo (user *u, int pid, field *field_changes, int field_changes_n) {
  dbg ("user_change_photo %d: photo_id = %d, field_changes_n = %d\n", u->id, pid, field_changes_n);

  if (write_only) {
    return 1;
  }

  assert (user_loaded (u));

  int aid = user_get_aid_by_pid (u, pid);
  if (aid == 0) {
    return 0;
  }
  data *d = user_get_photo_data (u, aid);
  if (d == NULL) {
    return 0;
  }

  if (data_get_hidden_state (d, pid) != 0) {
    return 0;
  }

  int i;
  for (i = 0; i < field_changes_n; i++) {
    assert (field_changes[i].v_fid != photo_type_id && field_changes[i].v_fid != photo_type_owner_id);

    // change album
    if (field_changes[i].v_fid == photo_type_album_id) {
      int naid = field_changes[i].v_int;
      if (aid == naid) {
        continue;
      }

      dbg ("Move (photo_id = %d) to (album_id = %d) (field_changes_n = %d)\n", pid, field_changes[i].v_int, field_changes_n);

      if (!check_album_id (naid)) {
        return 0;
      }

      if (naid < 0) {
        user_create_album_force (u, naid);
      }

      data *da = user_get_photo_data (u, naid);
      if (da == NULL) {
        return 0;
      }

      if (data_get_cnt (da) + 1 > GET_MAX_PHOTOS (naid)) {
        return 0;
      }

      actual_object o;
      int lid = data_get_local_id_by_id (d, pid);
      assert (lid >= 0);

      assert (data_get_actual_object (d, lid, &o) >= 0);

      event *ne = event_update_event (o.obj, o.dyn, PHOTO_TYPE);
      if (ne == o.obj) {
        ne = event_dup (ne);
      }

      data_del (d, pid);

      lid = data_add_object (da, pid);
      assert (lid >= 0);

      my_change ch;
      ch.tp = ch_event;
      ch.e = ne;

      data_add_change (da, (change *)&ch, lid);
      lookup_set (&u->album_by_photo, pid, naid);

      d = da;

//      dbg ("Move (photo_id = %d) to (album_id = %d) (field_changes_n = %d)\n", pid, field_changes[i].v_int, field_changes_n);
    }
  }

  return user_change_data (d, pid, field_changes, field_changes_n, 0) > -1;
}