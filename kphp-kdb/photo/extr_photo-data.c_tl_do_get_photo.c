#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  local_id; } ;
typedef  TYPE_1__ user ;
struct tl_get_photo {int /*<<< orphan*/  mask; int /*<<< orphan*/  force; int /*<<< orphan*/  photo_id; int /*<<< orphan*/  user_id; } ;
struct tl_act_extra {scalar_t__ extra; } ;
typedef  int /*<<< orphan*/  actual_object ;

/* Variables and functions */
 int /*<<< orphan*/  NOAIO ; 
 int /*<<< orphan*/  PHOTO_TYPE ; 
 int /*<<< orphan*/  TL_MAYBE_FALSE ; 
 int /*<<< orphan*/  TL_MAYBE_TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ check_photo_id (int /*<<< orphan*/ ) ; 
 scalar_t__ check_user_id (int /*<<< orphan*/ ) ; 
 TYPE_1__* conv_uid_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_to_rpc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_mode ; 
 int /*<<< orphan*/  load_user_metafile (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 
 scalar_t__ user_get_photo (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_loaded (TYPE_1__*) ; 
 int /*<<< orphan*/  write_only ; 

int tl_do_get_photo (struct tl_act_extra *extra) {
  struct tl_get_photo *e = (struct tl_get_photo *)extra->extra;

  assert (check_user_id (e->user_id) && check_photo_id (e->photo_id));
  assert (!index_mode && !write_only);

  user *u = conv_uid_get (e->user_id);
  if (u == NULL) {
    tl_store_int (TL_MAYBE_FALSE);
    return 0;
  }

  load_user_metafile (u, u->local_id, NOAIO);
  if (!user_loaded (u)) {
    return -2;
  }

  actual_object o;
  if (user_get_photo (u, e->photo_id, e->force, &o) < 0) {
    tl_store_int (TL_MAYBE_FALSE);
    return 0;
  }

  tl_store_int (TL_MAYBE_TRUE);
  event_to_rpc (&o, PHOTO_TYPE, e->mask);
  return 0;
}