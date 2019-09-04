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
typedef  int /*<<< orphan*/  actual_object ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 char* event_get_location (int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ user_get_photo (int /*<<< orphan*/ *,int,int const,int /*<<< orphan*/ *) ; 
 scalar_t__ user_loaded (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_only ; 

char *user_photo_get_location (user *u, int pid, int original, const int force, int *len) {
  assert (user_loaded (u) && !write_only);

//  dbg ("user_photo_get_location (uid = %d) (pid = %d)\n", u->id, pid);

  actual_object o;
  if (user_get_photo (u, pid, force, &o) < 0) {
    return NULL;
  }
  return event_get_location (&o, original, len);
}