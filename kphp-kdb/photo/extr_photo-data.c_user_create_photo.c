#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int current_photo_id; } ;
typedef  TYPE_1__ user ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 scalar_t__ GET_MAX_PHOTOS (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_album_id (int) ; 
 scalar_t__ data_get_cnt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_create_album_force (TYPE_1__*,int) ; 
 int user_create_photo_internal (TYPE_1__*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/ * user_get_photo_data (TYPE_1__*,int) ; 
 int user_loaded (TYPE_1__*) ; 
 scalar_t__ write_only ; 

int user_create_photo (user *u, int aid, int cnt) {
//  dbg ("user_create_photo %d: album_id = %d, cnt = %d\n", u->id, aid, cnt);
  if (!check_album_id (aid)) {
    return 0;
  }

  if (write_only) {
    int res = u->current_photo_id;

    u->current_photo_id += cnt;

//    dbg ("write only\n");
    return res;
  }

  assert (user_loaded (u));

  int res = u->current_photo_id;

  if (aid < 0) {
    user_create_album_force (u, aid);
  }

  data *d = user_get_photo_data (u, aid);
  if (d == NULL || data_get_cnt (d) + cnt > GET_MAX_PHOTOS (aid)) {
    u->current_photo_id += cnt;
//    dbg ("user_create_photo %d: failed\n", u->id);
    return 0;
  }

  int ret = user_create_photo_internal (u, d, aid, cnt, res);
  assert (ret == cnt);

  u->current_photo_id += cnt;
//  dbg ("user_create_photo %d: done (photo_id = %d)", u->id, res);
  return res;
}