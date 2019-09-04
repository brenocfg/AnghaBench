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
struct TYPE_3__ {long long x; int y; } ;
typedef  TYPE_1__ pair_ll_int ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int*) ; 
 int* map_ll_int_add (int /*<<< orphan*/ *,long long) ; 
 int now ; 
 int /*<<< orphan*/  remove_expired_deletes_by_task_id () ; 
 int /*<<< orphan*/  task_deletes ; 
 int /*<<< orphan*/  task_id_to_delete_time ; 
 int /*<<< orphan*/  vector_pb (int /*<<< orphan*/ ,TYPE_1__) ; 

int delete_letters_by_task_id (long long task_id) {
  remove_expired_deletes_by_task_id();

  if (task_id != 0) {
    int *y = map_ll_int_add (&task_id_to_delete_time, task_id);
    assert (y);
    if (*y != now) {
      *y = now;
      pair_ll_int task_delete = {
        .x = task_id,
        .y = now
      };

      vector_pb (task_deletes, task_delete);
    }
    return 1;
  }
  return 0;
}