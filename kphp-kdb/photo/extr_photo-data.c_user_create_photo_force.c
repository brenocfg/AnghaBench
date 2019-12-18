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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_album_id (int) ; 
 int /*<<< orphan*/  check_photo_id (int) ; 
 scalar_t__ data_get_cnt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_create_album_force (TYPE_1__*,int) ; 
 int user_create_photo_internal (TYPE_1__*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/ * user_get_photo_data (TYPE_1__*,int) ; 
 int /*<<< orphan*/  user_loaded (TYPE_1__*) ; 
 scalar_t__ write_only ; 

int user_create_photo_force (user *u, int aid, int cnt, int pid) {
//  dbg ("user_create_photo_force %d: album_id = %d, cnt = %d, photo_id = %d\n", u->id, aid, cnt, pid);

  if (!check_photo_id (pid) || !check_album_id (aid) || pid + cnt > u->current_photo_id) {
    return -1;
  }

  if (write_only) {
    return 1;
  }

  assert (user_loaded (u));

  if (aid < 0) {
    user_create_album_force (u, aid);
  }

  data *d = user_get_photo_data (u, aid);
  if (d == NULL || data_get_cnt (d) + cnt > GET_MAX_PHOTOS (aid)) {
    return -1;
  }

  return user_create_photo_internal (u, d, aid, cnt, pid);
}