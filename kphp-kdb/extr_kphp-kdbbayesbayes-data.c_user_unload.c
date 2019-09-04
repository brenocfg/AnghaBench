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
 int /*<<< orphan*/  cur_users ; 
 int /*<<< orphan*/  del_user_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int ltbl_get_rev (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unload_user_metafile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_loaded (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_table ; 
 int /*<<< orphan*/ * users ; 

void user_unload (user *u) {
  assert (u != NULL);

  if (!user_loaded (u)) {
    fprintf (stderr, "%d\n", ltbl_get_rev (&user_table, (int)(u - users)));
    assert (0);
    return;
  }

  del_user_used (u);
  unload_user_metafile (u);
  cur_users--;
  assert (!user_loaded (u));
}