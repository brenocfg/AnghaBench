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
typedef  scalar_t__ global_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  OTree ; 
 int* R_end ; 
 int R_mode ; 
 int /*<<< orphan*/  SMALL_NODE (void*) ; 
 int barray_out_node (int /*<<< orphan*/ ,int) ; 
 int btree_out_node (int /*<<< orphan*/ ) ; 
 void* listree_lookup_large (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  store_object_id (int**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int b_out_g (object_id_t object_id, global_id_t global_id) {
  int m = R_mode;
  if (m & 0x6c0) {
    int temp_id = -1;
    tree_ext_large_t *T = listree_lookup_large (&OTree, object_id, &temp_id);
    if (T != (void *) -1) {
      return btree_out_node (SMALL_NODE(T));
    } else {
      return barray_out_node (0, temp_id);
    }
  } else {
    int *p = R_end;
    store_object_id (&p, object_id);
    if (m & 256) {
      *p++ = (int)global_id;
    }
    R_end = p;
  }
  return 0;
}