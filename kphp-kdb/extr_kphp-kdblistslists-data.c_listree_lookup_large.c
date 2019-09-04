#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void tree_ext_large_t ;
typedef  int /*<<< orphan*/  object_id_t ;
struct TYPE_5__ {void** root; int N; } ;
typedef  TYPE_1__ listree_direct_t ;

/* Variables and functions */
 void* LARGE_NODE (int /*<<< orphan*/ ) ; 
 scalar_t__ NIL ; 
 scalar_t__ NODE_TYPE (void*) ; 
 scalar_t__ SMALL_NODE (void*) ; 
 scalar_t__ TF_MINUS ; 
 int find_rpos_direct (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_data_direct (TYPE_1__*,int) ; 
 int /*<<< orphan*/  object_id_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_ext_lookup (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree_ext_large_t *listree_lookup_large (listree_direct_t *LD, object_id_t x, int *index) {
  int rpos;
  tree_ext_large_t *T = LARGE_NODE (tree_ext_lookup (SMALL_NODE (*LD->root), x));
  if (SMALL_NODE (T) == NIL) {
    rpos = find_rpos_direct (LD, x);
    if (rpos == 0) {
      return 0;
    }
    rpos = LD->N - rpos;
    if (!object_id_equal (get_data_direct (LD, rpos), x)) {
      return 0;
    }
    *index = rpos;
    return (void *)-1;
  } else {
    if (NODE_TYPE (T) == TF_MINUS) {
      return 0;
    }
    return T;
  }
}