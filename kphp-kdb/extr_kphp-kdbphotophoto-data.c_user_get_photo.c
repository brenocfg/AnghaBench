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
typedef  int /*<<< orphan*/  actual_object ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int user_get_aid_by_pid (int /*<<< orphan*/ *,int) ; 
 int user_get_obj (int /*<<< orphan*/ *,int,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * user_get_photo_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  user_loaded (int /*<<< orphan*/ *) ; 

int user_get_photo (user *u, int pid, const int force, actual_object *o) {
  assert (user_loaded (u));

  int aid = user_get_aid_by_pid (u, pid);
  if (aid == 0) {
    dbg ("no album found (pid->aid)\n");
    return -1;
  }
  data *d = user_get_photo_data (u, aid);
  if (d == NULL) {
    dbg ("no album data found\n");
    return -1;
  }
  return user_get_obj (d, pid, force, o);
}