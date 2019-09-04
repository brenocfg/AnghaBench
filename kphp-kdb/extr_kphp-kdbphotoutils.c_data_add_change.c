#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dyn_object ;
struct TYPE_5__ {int /*<<< orphan*/  dyn_snapshots; } ;
typedef  TYPE_1__ data ;
typedef  int /*<<< orphan*/  change ;
struct TYPE_6__ {int /*<<< orphan*/  (* add_change ) (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_3__* DATA_FUNC (TYPE_1__*) ; 
 scalar_t__ map_int_vptr_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  map_int_vptr_del (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int data_add_change (data *d, change *ch, int local_id) {
//  int pos = data_get_pos_by_local_id (d, local_id);
//  dbg ("ADD CHANGE to (local_id = %d) (pos = %d)\n", local_id, pos);

  dyn_object **dyn_obj = (dyn_object **)map_int_vptr_add (&d->dyn_snapshots, local_id + 1);
  DATA_FUNC(d)->add_change(dyn_obj, ch);
  if (*dyn_obj == NULL) {
    map_int_vptr_del (&d->dyn_snapshots, local_id + 1);
  }
//  map_int_vptr_foreach (&d->dyn_snapshots, tmp_dbg);
  return 0;
}