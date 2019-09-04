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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ map_int_vptr_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  map_int_vptr_del (int /*<<< orphan*/ *,int) ; 
 scalar_t__ map_int_vptr_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * restore_list_alloc (int) ; 
 int /*<<< orphan*/  restore_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_list_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * restore_list_pop_front (int /*<<< orphan*/ *) ; 

void data_restore_append (data *d, int a, int b) {
  restore_list **b_list_ptr = (restore_list **)map_int_vptr_get (&d->restore_info, b);
  if (b_list_ptr != NULL) {
    restore_list *b_list = *b_list_ptr;
    assert (!restore_list_is_empty (b_list));

    restore_list **a_list_ptr = (restore_list **)map_int_vptr_add (&d->restore_info, a);
    if (*a_list_ptr == NULL) {
      *a_list_ptr = restore_list_alloc(a);
    }
    restore_list *a_list = *a_list_ptr;

    b_list = restore_list_pop_front (b_list);
    restore_list_append (a_list, b_list);
    //restore_list_check (a_list);
    map_int_vptr_del (&d->restore_info, b);
  }
}