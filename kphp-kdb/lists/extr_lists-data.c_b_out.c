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
typedef  void tree_ext_large_t ;
typedef  int /*<<< orphan*/  object_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  OTree ; 
 int /*<<< orphan*/  R_end ; 
 int R_mode ; 
 int /*<<< orphan*/  SMALL_NODE (void*) ; 
 int barray_out_node (int /*<<< orphan*/ ,int) ; 
 int btree_out_node (int /*<<< orphan*/ ) ; 
 void* listree_lookup_large (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  store_object_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int b_out (object_id_t object_id) {
  int m = R_mode;
  if (m & 0x7c0) {
    int temp_id = -1;
    tree_ext_large_t *T = listree_lookup_large (&OTree, object_id, &temp_id);
    if (T != (void *) -1) {
      return btree_out_node (SMALL_NODE(T));
    } else {
      return barray_out_node (0, temp_id);
    }
  } else {
    store_object_id (&R_end, object_id);
  }
  return 0;
}