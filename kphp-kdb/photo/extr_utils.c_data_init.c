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
typedef  int /*<<< orphan*/  data_functions ;
struct TYPE_3__ {int objects_n; int /*<<< orphan*/  restore_info; int /*<<< orphan*/  dyn_snapshots; int /*<<< orphan*/  prm; int /*<<< orphan*/  hidden_state; int /*<<< orphan*/  id_to_local_id; scalar_t__ new_objects_n; int /*<<< orphan*/ * objects_offset; int /*<<< orphan*/ * objects; int /*<<< orphan*/ * func; } ;
typedef  TYPE_1__ data ;

/* Variables and functions */
 int /*<<< orphan*/  PERM (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init ; 
 int /*<<< orphan*/  lookup_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_int_vptr_init (int /*<<< orphan*/ *) ; 

void data_init (data *d, data_functions *f) {
  d->func = f;
  d->objects_n = -2;
  d->objects = NULL;
  d->objects_offset = NULL;
  d->new_objects_n = 0;
  lookup_init (&d->id_to_local_id);
  lookup_init (&d->hidden_state);
  //d->ids = NULL;
  //d->old_perm = NULL;
  PERM (init, &d->prm);
  map_int_vptr_init (&d->dyn_snapshots);
  map_int_vptr_init (&d->restore_info);
}