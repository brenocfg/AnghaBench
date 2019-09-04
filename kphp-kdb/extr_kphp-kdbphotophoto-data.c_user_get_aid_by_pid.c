#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  album_by_photo; } ;
typedef  TYPE_1__ user ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int data_get_local_id_by_id (int /*<<< orphan*/ *,int) ; 
 int lookup_conv (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * user_get_album_data (TYPE_1__*) ; 
 int user_loaded (TYPE_1__*) ; 

int user_get_aid_by_pid (user *u, int pid) {
//  dbg ("user_get_aid_by_pid %d: photo_id = %d\n", u->id, pid);

  assert (user_loaded (u));
  int res = lookup_conv (&u->album_by_photo, pid, 0);

//  dbg ("photo_id = %d, album_id = %d\n", pid, res);
//  can be deleted, I hope
  if (res != 0) {
    data *albums = user_get_album_data (u);
    assert (data_get_local_id_by_id (albums, res) != -1);
  }

  return res;
}