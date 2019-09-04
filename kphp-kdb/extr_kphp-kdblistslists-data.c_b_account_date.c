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
 int /*<<< orphan*/  SMALL_NODE (void*) ; 
 int barray_account_date (int /*<<< orphan*/ ,int) ; 
 int btree_account_date (int /*<<< orphan*/ ) ; 
 void* listree_lookup_large (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline int b_account_date (object_id_t object_id) {
  int temp_id = -1;
  tree_ext_large_t *T = listree_lookup_large (&OTree, object_id, &temp_id);
  if (T != (void *) -1) {
    return btree_account_date (SMALL_NODE(T));
  } else {
    return barray_account_date (0, temp_id);
  }
}