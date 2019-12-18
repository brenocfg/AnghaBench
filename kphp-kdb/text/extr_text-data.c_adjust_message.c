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
 int adjust_message_intermediate (int,int,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ conv_uid (int) ; 
 int /*<<< orphan*/ * get_user_f (int) ; 
 int /*<<< orphan*/  update_history_persistent (int /*<<< orphan*/ *,int,int,int) ; 
 scalar_t__ write_all_events ; 

int adjust_message (int user_id, int local_id, int clear_mask, int set_mask, int from_binlog) {
  if (clear_mask != -1 || set_mask != -1) {
    clear_mask &= 0xffff;
    set_mask &= 0xffff;
    assert (!(clear_mask & set_mask));
  }

  if (conv_uid (user_id) < 0 || local_id <= 0) {
    return -1;
  }

  int res = adjust_message_intermediate (user_id, local_id, clear_mask, set_mask);

  if (from_binlog || (res & 1) || (res >= 0 && write_all_events)) {
    user_t *U = get_user_f (user_id);
    if (clear_mask < 0) {
      update_history_persistent (U, local_id, 0, 0);
    } else if ((clear_mask | set_mask) == 0xffff) {
      update_history_persistent (U, local_id, set_mask, 1);
    } else {
      if (clear_mask) {
	assert (!set_mask);
	update_history_persistent (U, local_id, clear_mask, 3);
      } else {
	assert (!clear_mask);
	update_history_persistent (U, local_id, set_mask, 2);
      }
    }
  }

  return res;
}