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
 int /*<<< orphan*/  load_g_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_g_tree_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  load_o_tree_sub (int /*<<< orphan*/ *,int) ; 
 int lrand48 () ; 

__attribute__((used)) static inline void delete_list_entry_aux (object_id_t object_id, global_id_t global_id, int flags) {
  int cat = flags & (SUBCATS - 1);
  listree_t OTreeSub;
  listree_xglobal_t GTree, GTreeSub;
  load_o_tree_sub (&OTreeSub, cat);
  load_g_tree (&GTree);
  load_g_tree_sub (&GTreeSub, cat);
  listree_delete_small (&OTreeSub, object_id, lrand48 ()/*global_id * Y_MULT*/);
  #ifdef LISTS_GT
  listree_delete_global (&GTree, global_id, object_id);
  listree_delete_global (&GTreeSub, global_id, object_id);
  #else
  listree_delete_small (&GTree, global_id, object_id * Y_MULT);
  listree_delete_small (&GTreeSub, global_id, object_id * Y_MULT);
  #endif
}