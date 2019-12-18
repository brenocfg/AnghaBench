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

/* Variables and functions */
 int /*<<< orphan*/ * UserMsgDel ; 
 int /*<<< orphan*/ * UserMsgExtras ; 
 int /*<<< orphan*/  assert (int) ; 
 int conv_uid (int) ; 
 int current_extra_mask ; 
 int /*<<< orphan*/  discarded_rec ; 
 scalar_t__ extra_mask_intcount (int) ; 

void adjust_message0 (int user_id, int local_id, int flags, int op, int *extra) {
  int uid = conv_uid (user_id);
  if (uid < 0 || local_id <= 0) {
    discarded_rec++;
    return;
  }
  UserMsgDel[uid]++;
  if (extra) {
    assert (!(flags & ~current_extra_mask) && flags);
    UserMsgExtras[uid] += extra_mask_intcount (flags & current_extra_mask);
  }
}