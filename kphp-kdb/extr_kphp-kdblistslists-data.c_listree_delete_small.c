#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ tree_ext_small_t ;
typedef  int /*<<< orphan*/  object_id_t ;
struct TYPE_19__ {scalar_t__ N; TYPE_1__** root; } ;
typedef  TYPE_2__ listree_t ;

/* Variables and functions */
 TYPE_1__* DeletedSubnode ; 
 int /*<<< orphan*/  MAKE_RPOS (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* NIL ; 
 scalar_t__ NODE_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  TF_MINUS ; 
 scalar_t__ TF_PLUS ; 
 int /*<<< orphan*/  assert (int) ; 
 int find_rpos_indirect (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_tree_ext_small_node (TYPE_1__*) ; 
 int /*<<< orphan*/  get_data_indirect (TYPE_2__*,scalar_t__) ; 
 TYPE_1__* new_tree_subnode_small (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ object_id_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* tree_ext_delete (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* tree_ext_insert (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* tree_ext_lookup (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void listree_delete_small (listree_t *LI, object_id_t x, int y) {
  tree_ext_small_t **R = LI->root;
  int rpos;
  tree_ext_small_t *T = tree_ext_lookup (*R, x);

  if (T == NIL) {
    rpos = find_rpos_indirect (LI, x);
    assert (rpos > 0 && object_id_equal (get_data_indirect (LI, LI->N - rpos), x));
    tree_ext_small_t *node = new_tree_subnode_small (x, y, MAKE_RPOS (rpos, TF_MINUS));
    *R = tree_ext_insert (*R, node->x, node->y, node);
  } else {
    assert (NODE_TYPE(T) == TF_PLUS);
    DeletedSubnode = 0;
    *R = tree_ext_delete (*R, x);
    assert (DeletedSubnode == T);
    free_tree_ext_small_node (T);
  }
}