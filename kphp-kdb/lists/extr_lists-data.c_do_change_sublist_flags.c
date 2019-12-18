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
struct lev_sublist_flags {int xor_cond; int and_cond; int and_set; int xor_set; } ;
struct lev_generic {int dummy; } ;
typedef  int /*<<< orphan*/  list_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_INT (int /*<<< orphan*/ ) ; 
 struct lev_sublist_flags* LEV_ADJUST_L (struct lev_sublist_flags*) ; 
 int /*<<< orphan*/  LEV_LI_SUBLIST_FLAGS ; 
 struct lev_sublist_flags* alloc_log_event (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int change_sublist_flags (int /*<<< orphan*/ ,int,struct lev_generic*) ; 
 scalar_t__ conv_list_id (int /*<<< orphan*/ ) ; 
 scalar_t__ lev_list_id_bytes ; 
 scalar_t__ metafile_mode ; 
 scalar_t__ prepare_list_metafile (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  upcopy_list_id (struct lev_sublist_flags*,int /*<<< orphan*/ ) ; 

int do_change_sublist_flags (list_id_t list_id, int xor_cond, int and_cond, int and_set, int xor_set) {
  if (conv_list_id (list_id) < 0) {
    return -1;
  }
  if (metafile_mode && prepare_list_metafile (list_id, 1) < 0) {
    return -2;
  }
  struct lev_sublist_flags *EE, *E = alloc_log_event (LEV_LI_SUBLIST_FLAGS, sizeof (struct lev_sublist_flags) + lev_list_id_bytes, FIRST_INT (list_id));
  upcopy_list_id (E, list_id);
  EE = LEV_ADJUST_L(E);
  EE->xor_cond = xor_cond;
  EE->and_cond = and_cond;
  EE->and_set = and_set;
  EE->xor_set = xor_set;
  return change_sublist_flags (list_id, *(int *) &(EE->xor_cond), (struct lev_generic *)E);
}