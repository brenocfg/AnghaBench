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
typedef  int /*<<< orphan*/  user_t ;

/* Variables and functions */
 int /*<<< orphan*/ * get_user_f (int) ; 
 int /*<<< orphan*/  update_history (int /*<<< orphan*/ *,int,int,int) ; 

int do_update_history (int user_id, int local_id, int flags, int op) {
  if (op < 50 || op >= 100 || flags & ~0xffff) {
    return -1;
  }
  user_t *U = get_user_f (user_id);
  if (!U) {
    return -1;
  }
  update_history (U, local_id, flags, op);
  return 1;
}