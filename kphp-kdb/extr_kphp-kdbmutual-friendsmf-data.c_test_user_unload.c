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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * conv_uid (int) ; 
 int /*<<< orphan*/  cur_users ; 
 int /*<<< orphan*/  del_user_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unbind_user_metafile (int /*<<< orphan*/ *) ; 
 scalar_t__ user_loaded (int /*<<< orphan*/ *) ; 
 int verbosity ; 

void test_user_unload (int uid) {
  if (verbosity > 2) {
    fprintf (stderr, "test user unload %d\n", uid);
  }

  user *u = conv_uid (uid);
  if (u == NULL) {
    return;
  }

  if (user_loaded (u)) {
    del_user_used (u);
    unbind_user_metafile (u);
    cur_users--;
  }

  assert (!user_loaded (u));
}