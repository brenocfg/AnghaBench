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
struct TYPE_5__ {int /*<<< orphan*/  restore_info; int /*<<< orphan*/  dyn_snapshots; int /*<<< orphan*/  prm; int /*<<< orphan*/  hidden_state; int /*<<< orphan*/  id_to_local_id; } ;
typedef  TYPE_1__ data ;
struct TYPE_6__ {int /*<<< orphan*/  free_dyn; } ;

/* Variables and functions */
 TYPE_3__* DATA_FUNC (TYPE_1__*) ; 
 int /*<<< orphan*/  PERM (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  free_restore_list ; 
 int /*<<< orphan*/  lookup_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_int_vptr_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_int_vptr_free (int /*<<< orphan*/ *) ; 

void data_free (data *d) {
  lookup_free (&d->id_to_local_id);
  lookup_free (&d->hidden_state);

  PERM (free, &d->prm);
  map_int_vptr_foreach (&d->dyn_snapshots, DATA_FUNC(d)->free_dyn);
  map_int_vptr_free (&d->dyn_snapshots);


  map_int_vptr_foreach (&d->restore_info, free_restore_list);
  map_int_vptr_free (&d->restore_info);
}