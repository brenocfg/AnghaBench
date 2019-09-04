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
struct lev_generic {int dummy; } ;
struct lev_del_entry {int dummy; } ;
typedef  int /*<<< orphan*/  object_id_t ;
typedef  int /*<<< orphan*/  list_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEV_LI_DEL_ENTRY ; 
 struct lev_del_entry* alloc_log_event (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ conv_list_id (int /*<<< orphan*/ ) ; 
 int delete_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct lev_generic*) ; 
 scalar_t__ lev_list_object_bytes ; 
 scalar_t__ metafile_mode ; 
 scalar_t__ prepare_list_metafile (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  upcopy_list_object_id (struct lev_del_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int do_delete_list_entry (list_id_t list_id, object_id_t object_id) {
  if (conv_list_id (list_id) < 0) {
    return -1;
  }
  if (metafile_mode && prepare_list_metafile (list_id, 1) < 0) {
    return -2;
  }

  struct lev_del_entry *E = alloc_log_event (LEV_LI_DEL_ENTRY, sizeof (struct lev_del_entry) + lev_list_object_bytes, FIRST_INT (list_id));
  upcopy_list_object_id (E, list_id, object_id);

  return delete_entry (list_id, object_id, 1, (struct lev_generic *)E);
}