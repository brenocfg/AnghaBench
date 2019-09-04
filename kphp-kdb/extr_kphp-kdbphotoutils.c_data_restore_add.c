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
typedef  int /*<<< orphan*/  restore_list ;
struct TYPE_3__ {int /*<<< orphan*/  restore_info; } ;
typedef  TYPE_1__ data ;

/* Variables and functions */
 scalar_t__ map_int_vptr_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  map_int_vptr_del (int /*<<< orphan*/ *,int) ; 
 scalar_t__ map_int_vptr_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * restore_list_alloc (int) ; 
 int /*<<< orphan*/  restore_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void data_restore_add (data *d, int id, int prev_id) {
//  dbg ("data_restore_add (id = %d) (prev_id = %d)\n", id, prev_id);
  restore_list **prev_id_list_ptr = (restore_list **)map_int_vptr_add (&d->restore_info, prev_id);
  if (*prev_id_list_ptr == NULL) {
    *prev_id_list_ptr = restore_list_alloc (prev_id);
  }
  restore_list *prev_id_list = *prev_id_list_ptr;

  restore_list **id_list_ptr = (restore_list **) map_int_vptr_get (&d->restore_info, id);
  restore_list *id_list;
  if (id_list_ptr == NULL) {
    id_list = restore_list_alloc (id);
  } else {
    id_list = *id_list_ptr;
    map_int_vptr_del (&d->restore_info, id);
  }

  restore_list_append (prev_id_list, id_list);
}