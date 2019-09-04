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
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int data_get_cnt (int /*<<< orphan*/ *) ; 
 scalar_t__ data_get_hidden_state (int /*<<< orphan*/ *,int) ; 
 int data_get_local_id_by_id (int /*<<< orphan*/ *,int) ; 
 int data_get_local_id_by_pos (int /*<<< orphan*/ *,int) ; 
 int data_get_pos_by_local_id (int /*<<< orphan*/ *,int) ; 
 int data_move_new (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  write_only ; 

inline int user_change_order (data *d, int id, int id_near, int is_next) {
//  dbg ("user_change_order ???: id = %d, id_near = %d, is_next = %d\n", id, id_near, is_next);

  assert (!write_only);

  if (data_get_hidden_state (d, id) != 0 || (id_near != 0 && data_get_hidden_state (d, id_near) != 0)) {
    return 0;
  }

  int i, j;

//  dbg ("user_change_order (id = %d) (id_near = %d)\n", id, id_near);
  int local_id = data_get_local_id_by_id (d, id);
  i = data_get_pos_by_local_id (d, local_id);
  if (i < 0) {
    return i;
  }

  int local_id_near;
  if (id_near != 0) {
    local_id_near = data_get_local_id_by_id (d, id_near);
    j = data_get_pos_by_local_id (d, local_id_near);
    if (j < 0) {
      return j;
    }
    if (is_next) {
      j--;
      local_id_near = data_get_local_id_by_pos (d, j);
    }
//    dbg ("user_change_order (i = %d) (j = %d)\n", i, j);
    if (i > j) {
      j++;
    }
  } else {
    if (is_next) {
      j = data_get_cnt (d) - 1;
      local_id_near = data_get_local_id_by_pos (d, j);
    } else {
      j = 0;
      local_id_near = -1;
    }
  }

  return data_move_new (d, i, j, local_id, local_id_near);
}