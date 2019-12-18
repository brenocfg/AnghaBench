#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  local_id; } ;
typedef  TYPE_3__ user ;
struct tl_change_photo {scalar_t__ changes_len; int /*<<< orphan*/  photo_id; int /*<<< orphan*/  user_id; int /*<<< orphan*/  changes; int /*<<< orphan*/  mask; } ;
struct tl_act_extra {scalar_t__ extra; } ;
struct TYPE_10__ {int /*<<< orphan*/  photo_len; int /*<<< orphan*/  photo; int /*<<< orphan*/  orig_album_id; int /*<<< orphan*/  orig_owner_id; int /*<<< orphan*/  server_id2; int /*<<< orphan*/  server_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  secret; int /*<<< orphan*/  extra; int /*<<< orphan*/  local_id; int /*<<< orphan*/  volume_id; int /*<<< orphan*/  rotate; int /*<<< orphan*/  size; } ;
struct TYPE_12__ {scalar_t__ v_fid; TYPE_2__ location_old; TYPE_1__ location_engine; scalar_t__ is_location_engine; } ;
typedef  TYPE_4__ location ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_PHOTO_CHANGE_PHOTO ; 
 scalar_t__ MAX_EVENT_SIZE ; 
 int /*<<< orphan*/  NOAIO ; 
 int /*<<< orphan*/  PHOTO_TYPE ; 
 int /*<<< orphan*/  TL_BOOL_FALSE ; 
 int /*<<< orphan*/  TL_BOOL_TRUE ; 
 int /*<<< orphan*/  TL_ERROR_BAD_VALUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ check_photo_id (int /*<<< orphan*/ ) ; 
 TYPE_3__* conv_uid (int /*<<< orphan*/ ) ; 
 int do_add_photo_location (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int do_add_photo_location_engine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int do_change_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ field_changes_n ; 
 int /*<<< orphan*/  load_user_metafile (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* location_changes ; 
 int location_changes_n ; 
 scalar_t__ photo_type__original_location ; 
 scalar_t__ rpc_get_fields (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_loaded (TYPE_3__*) ; 

int tl_do_change_photo (struct tl_act_extra *extra) {
  struct tl_change_photo *e = (struct tl_change_photo *)extra->extra;

  assert (check_photo_id (e->photo_id) && 0 < e->changes_len && e->changes_len < MAX_EVENT_SIZE);

  user *u = conv_uid (e->user_id);
  assert (u != NULL);

  load_user_metafile (u, u->local_id, NOAIO);
  if (!user_loaded (u)) {
    return -2;
  }

  if (rpc_get_fields (PHOTO_TYPE, e->mask, e->changes, e->changes_len) < 0) {
    tl_fetch_set_error_format (TL_ERROR_BAD_VALUE, "Can't parse changes");
    return -1;
  }

  int res = 1;
  if (field_changes_n != 0) {
    res &= do_change_data (e->user_id, e->photo_id, LEV_PHOTO_CHANGE_PHOTO);
  }
  int i;
  for (i = 0; i < location_changes_n; i++) {
    location *cur = &location_changes[i];
    if (cur->is_location_engine) {
      res &= do_add_photo_location_engine (
               e->user_id,
               e->photo_id,
               cur->v_fid == photo_type__original_location,
               cur->location_engine.size,
               cur->location_engine.rotate,
               cur->location_engine.volume_id,
               cur->location_engine.local_id,
               cur->location_engine.extra,
               cur->location_engine.secret);
    } else {
      res &= do_add_photo_location (
               e->user_id,
               e->photo_id,
               cur->v_fid == photo_type__original_location,
               cur->location_old.server_id,
               cur->location_old.server_id2,
               cur->location_old.orig_owner_id,
               cur->location_old.orig_album_id,
               cur->location_old.photo,
               cur->location_old.photo_len);
    }
  }

  tl_store_int (res ? TL_BOOL_TRUE : TL_BOOL_FALSE);
  return 0;
}