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
typedef  int object_id_t ;
typedef  int /*<<< orphan*/  listree_xglobal_t ;
typedef  int /*<<< orphan*/  listree_t ;
typedef  int global_id_t ;

/* Variables and functions */
 int SUBCATS ; 
 int Y_MULT ; 
 int /*<<< orphan*/  listree_delete_global (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  listree_delete_small (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  listree_insert_global (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  listree_insert_small (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  load_g_tree_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  load_o_tree_sub (int /*<<< orphan*/ *,int) ; 
 int lrand48 () ; 

__attribute__((used)) static inline void change_entry_flags_common (object_id_t object_id, global_id_t global_id, int oldflags, int flags) {
  int old_cat = oldflags & (SUBCATS - 1);
  int new_cat = flags & (SUBCATS - 1);
  if (new_cat != old_cat) {
    listree_t OT1, OT2;
    listree_xglobal_t GT1, GT2;
    load_o_tree_sub (&OT1, old_cat);  
    load_o_tree_sub (&OT2, new_cat);  
    load_g_tree_sub (&GT1, old_cat);  
    load_g_tree_sub (&GT2, new_cat);  
    listree_delete_small (&OT1, object_id, lrand48 ()/*global_id * Y_MULT*/);
    listree_insert_small (&OT2, object_id, lrand48 ()/*global_id * Y_MULT*/);
    #ifdef LISTS_GT
    listree_delete_global (&GT1, global_id, object_id);
    listree_insert_global (&GT2, global_id, object_id);
    #else
    listree_delete_small (&GT1, global_id, object_id * Y_MULT);
    listree_insert_small (&GT2, global_id, object_id * Y_MULT);
    #endif
  }
}