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
struct lev_del_obj {int dummy; } ;
typedef  int /*<<< orphan*/  object_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEV_LI_DEL_OBJ ; 
 void* alloc_log_event (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int delete_object (int /*<<< orphan*/ ) ; 
 scalar_t__ lev_object_id_bytes ; 
 scalar_t__ prepare_object_metafile (int /*<<< orphan*/ ,int) ; 
 scalar_t__ revlist_metafile_mode ; 
 int /*<<< orphan*/  upcopy_object_id (void*,int /*<<< orphan*/ ) ; 

int do_delete_object (object_id_t object_id) {
  if (revlist_metafile_mode && prepare_object_metafile (object_id, 1) < 0) {
    return -2;
  }
  void *E = alloc_log_event (LEV_LI_DEL_OBJ, sizeof (struct lev_del_obj) + lev_object_id_bytes, FIRST_INT(object_id));
  upcopy_object_id (E, object_id);
  return delete_object (object_id);
}