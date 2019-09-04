#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  data ;
struct TYPE_4__ {int /*<<< orphan*/  deleted; } ;
typedef  TYPE_1__ actual_object ;

/* Variables and functions */
 scalar_t__ data_get_actual_object (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  data_get_hidden_state (int /*<<< orphan*/ *,int) ; 
 int data_get_local_id_by_id (int /*<<< orphan*/ *,int) ; 

inline int user_get_obj (data *d, int id, const int force, actual_object *o) {
  int local_id = data_get_local_id_by_id (d, id);
  if (local_id < 0 || ((o->deleted = data_get_hidden_state (d, id)) != 0 && !force) || data_get_actual_object (d, local_id, o) < 0) {
    return -1;
  }
  return 0;
}