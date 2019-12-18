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
struct lev_set_flags {int dummy; } ;
struct lev_generic {int /*<<< orphan*/  a; } ;
struct lev_change_flags_long {int and_mask; int xor_mask; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  object_id_t ;
typedef  int /*<<< orphan*/  list_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_INT (int /*<<< orphan*/ ) ; 
 struct lev_change_flags_long* LEV_ADJUST_LO (struct lev_change_flags_long*) ; 
 int /*<<< orphan*/  LEV_LI_CHANGE_FLAGS_LONG ; 
 int set_entry_flags (struct lev_set_flags*) ; 
 int /*<<< orphan*/  upcopy_list_object_id (struct lev_change_flags_long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int create_change_entry_flags (list_id_t list_id, object_id_t object_id, int and_flags, int xor_flags) {
  static char buf[1024];
  struct lev_change_flags_long *E = (void *)buf; //alloc_log_event (LEV_LI_CHANGE_FLAGS_LONG, sizeof (struct lev_change_flags_long) + lev_list_object_bytes, FIRST_INT(list_id));
  E->type = LEV_LI_CHANGE_FLAGS_LONG;
  ((struct lev_generic *)E)->a = FIRST_INT(list_id);
  upcopy_list_object_id (E, list_id, object_id);
  struct lev_change_flags_long *EE = LEV_ADJUST_LO (E);
  EE->and_mask = and_flags;
  EE->xor_mask = xor_flags;
  return set_entry_flags ((struct lev_set_flags *) E);
}