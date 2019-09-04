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

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_loaded (int /*<<< orphan*/ *) ; 
 char* user_photo_get_location (int /*<<< orphan*/ *,int,int,int,int*) ; 
 int /*<<< orphan*/  user_photo_set_location (int /*<<< orphan*/ *,int,int,char*,int) ; 
 scalar_t__ write_only ; 

int user_save_photo_location (user *u, int pid) {
  if (write_only) {
    return 1;
  }

  assert (user_loaded (u));

  int len;
  char *loc = user_photo_get_location (u, pid, 1, 1, &len);

  if (len > 1) {
    return 0;
  }

  loc = user_photo_get_location (u, pid, 0, 1, &len);

  if (loc == NULL || len <= 1) {
    return 1;
  }

  user_photo_set_location (u, pid, 1, loc, len);
  user_photo_set_location (u, pid, 0, "", 1);

  return 1;
}