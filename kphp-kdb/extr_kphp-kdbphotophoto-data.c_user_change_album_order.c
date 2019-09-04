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
 int /*<<< orphan*/ * user_get_album_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_loaded (int /*<<< orphan*/ *) ; 
 scalar_t__ write_only ; 

int user_change_album_order (user *u, int aid, int aid_near, int is_next) {
//  dbg ("user_change_album_order %d: album_id = %d, album_id_near = %d, is_next = %d\n", u->id, aid, aid_near, is_next);

  if (write_only) {
    return 1;
  }

  assert (user_loaded (u));

  data *d = user_get_album_data (u);
  return user_change_order (d, aid, aid_near, is_next) > -1;
}