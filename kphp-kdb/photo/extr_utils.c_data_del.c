#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dyn_object ;
struct TYPE_8__ {int /*<<< orphan*/  dyn_snapshots; int /*<<< orphan*/  hidden_state; int /*<<< orphan*/  id_to_local_id; int /*<<< orphan*/  prm; } ;
typedef  TYPE_1__ data ;
struct TYPE_9__ {int /*<<< orphan*/  (* free_dyn ) (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ;} ;

/* Variables and functions */
 TYPE_6__* DATA_FUNC (TYPE_1__*) ; 
 int PERM (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int data_get_local_id_by_id (TYPE_1__*,int) ; 
 int data_get_pos_by_local_id (TYPE_1__*,int) ; 
 int /*<<< orphan*/  data_restore_append (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  del ; 
 int /*<<< orphan*/  get_i ; 
 int /*<<< orphan*/  lookup_set (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  map_int_vptr_del (int /*<<< orphan*/ *,int) ; 
 scalar_t__ map_int_vptr_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

int data_del (data *d, int id) {
//  dbg ("DATA_DEL %d\n", id);
  int local_id = data_get_local_id_by_id (d, id);
  if (local_id < 0) {
    return -1;
  }

  //*map_int_int_add (&d->new_id_to_i, id) = -1;
  int pos = data_get_pos_by_local_id (d, local_id);
  if (pos >= 0) {
    PERM (del, &d->prm, pos);

    int prev_local_id = pos == 0 ? -1 : PERM (get_i, &d->prm, pos - 1);
    data_restore_append (d, prev_local_id, local_id);
  }

  lookup_set (&d->id_to_local_id, id, -1);

  //TODO: lazy_set
  lookup_set (&d->hidden_state, id, 0);

  dyn_object **dyn_obj = (dyn_object **)map_int_vptr_get (&d->dyn_snapshots, local_id + 1);
  if (dyn_obj != NULL) {
    DATA_FUNC(d)->free_dyn (NULL, dyn_obj);
    map_int_vptr_del (&d->dyn_snapshots, local_id + 1);
  }

  return 0;
}