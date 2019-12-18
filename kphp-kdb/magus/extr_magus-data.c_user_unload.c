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
 int /*<<< orphan*/  unload_user_metafile (int /*<<< orphan*/ *) ; 
 int user_loaded (int /*<<< orphan*/ *) ; 

void user_unload (user *u) {
  assert (user_loaded (u));

  del_user_used (u);
  unload_user_metafile (u);
  cur_users--;

  assert (!user_loaded (u));
}