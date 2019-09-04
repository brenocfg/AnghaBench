#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int val; } ;
typedef  TYPE_1__ restore_list ;
struct TYPE_9__ {int /*<<< orphan*/  restore_info; } ;
typedef  TYPE_2__ data ;

/* Variables and functions */
 int _found ; 
 TYPE_1__* _found_a ; 
 TYPE_1__* _found_b ; 
 int _needed_id ; 
 int* _prev_id ; 
 scalar_t__ map_int_vptr_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  map_int_vptr_del (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  map_int_vptr_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_list_free (TYPE_1__*) ; 
 scalar_t__ restore_list_is_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  search_for_id ; 

int data_restore_del (data *d, int needed_id, int *prev_id) {
//  dbg ("data_restore_del\n");
  _prev_id = prev_id;
  _found = -1;
  _needed_id = needed_id;
  _prev_id = prev_id;
  map_int_vptr_foreach (&d->restore_info, search_for_id);

//  dbg ("_found = %d\n", _found);
  if (_found > 0) {
    if (restore_list_is_empty (_found_a)) {
      int a = _found_a->val;
      restore_list_free (_found_a);
      map_int_vptr_del (&d->restore_info, a);
    }

    if (restore_list_is_empty (_found_b)) {
      restore_list_free (_found_b);
    } else {
      int  b = _found_b->val;
      *(restore_list **)map_int_vptr_add (&d->restore_info, b) = _found_b;
    }
  }

  return _found;
}