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
 int* map_ll_int_get (int /*<<< orphan*/ *,long long) ; 
 int /*<<< orphan*/  remove_expired_deletes_by_task_id () ; 
 int /*<<< orphan*/  task_id_to_delete_time ; 

int is_deleted_task (long long task_id, int time_received) {
  remove_expired_deletes_by_task_id();

  if (task_id != 0) {
    int *y = map_ll_int_get (&task_id_to_delete_time, task_id);
    if (y != NULL && *y >= time_received) {
      return 1;
    }
  }
  return 0;
}