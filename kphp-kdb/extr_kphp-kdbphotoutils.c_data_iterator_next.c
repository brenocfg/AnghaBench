#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t ids_i; size_t ids_end; size_t new_ids_i; size_t new_ids_end; int* ids; int dir; int* new_ids; int* new_local_ids; int* old_perm; int id; int local_id; int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ data_iterator ;

/* Variables and functions */
 scalar_t__ data_get_hidden_state (int /*<<< orphan*/ ,int) ; 

int data_iterator_next (data_iterator *it) {
  //dbg ("data_iterator_next (ids_i = %d) (new_ids_i = %d)\n", it->ids_i, it->new_ids_i);
  while (it->ids_i != it->ids_end || it->new_ids_i != it->new_ids_end) {
    int id, local_id;
    if (it->new_ids_i == it->new_ids_end || (it->ids_i != it->ids_end && it->ids[it->ids_i] * it->dir <= it->new_ids[it->new_ids_i] * it->dir)) {
      if (it->new_ids_i != it->new_ids_end && it->ids[it->ids_i] == it->new_ids[it->new_ids_i]) {
        id = it->new_ids[it->new_ids_i];
        local_id = it->new_local_ids[it->new_ids_i];

        it->new_ids_i += it->dir;
        it->ids_i += it->dir;
      } else {
        id = it->ids[it->ids_i];
        local_id = it->old_perm[it->ids_i];
        it->ids_i += it->dir;
      }
    } else {
      id = it->new_ids[it->new_ids_i];
      local_id = it->new_local_ids[it->new_ids_i];
      it->new_ids_i += it->dir;
    }
    if (local_id >= 0 && data_get_hidden_state (it->d, id) == 0) {

      //dbg ("next (id = %d) (local_id = %d)\n", id, local_id);
      it->id = -id * it->dir;
      it->local_id = local_id;
      return 1;
    }
  }
  return 0;
}