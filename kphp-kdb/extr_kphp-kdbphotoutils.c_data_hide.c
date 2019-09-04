#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  prm; int /*<<< orphan*/  hidden_state; } ;
typedef  TYPE_1__ data ;

/* Variables and functions */
 int PERM (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int data_get_local_id_by_id (TYPE_1__*,int) ; 
 int data_get_pos_by_local_id (TYPE_1__*,int) ; 
 int /*<<< orphan*/  data_restore_add (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  del ; 
 int /*<<< orphan*/  get_i ; 
 int /*<<< orphan*/  lookup_set (int /*<<< orphan*/ *,int,int) ; 

int data_hide (data *d, int id, int tm) {
  int local_id = data_get_local_id_by_id (d, id);
  if (local_id < 0) {
    return -1;
  }

  int pos = data_get_pos_by_local_id (d, local_id);
  assert (pos >= 0);

  int prev_local_id = pos == 0 ? -1 : PERM (get_i, &d->prm, pos - 1);
  data_restore_add (d, local_id, prev_local_id);

  lookup_set (&d->hidden_state, id, tm);

  return PERM (del, &d->prm, pos);
}