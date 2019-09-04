#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int rpos; } ;
typedef  TYPE_1__ tree_ext_small_t ;
struct TYPE_18__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ tree_ext_large_t ;
typedef  int /*<<< orphan*/  object_id_t ;
struct TYPE_19__ {scalar_t__ N; TYPE_2__** root; } ;
typedef  TYPE_3__ listree_direct_t ;

/* Variables and functions */
 TYPE_2__* LARGE_NODE (TYPE_1__*) ; 
 int /*<<< orphan*/  MAKE_RPOS (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* NIL ; 
 scalar_t__ NODE_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  SMALL_NODE (TYPE_2__*) ; 
 scalar_t__ TF_MINUS ; 
 int /*<<< orphan*/  TF_PLUS ; 
 int /*<<< orphan*/  assert (int) ; 
 int find_rpos_direct (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_data_direct (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  lrand48 () ; 
 TYPE_2__* new_tree_subnode_large (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_id_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* tree_ext_adjust_deltas (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* tree_ext_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* tree_ext_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree_ext_large_t *listree_insert_large (listree_direct_t *LD, object_id_t x) {
  tree_ext_large_t **R = LD->root;
  int rpos;
  tree_ext_small_t *T = tree_ext_lookup (SMALL_NODE (*R), x);
  if (T == NIL) {
    rpos = find_rpos_direct (LD, x);
    assert (!rpos || !object_id_equal (get_data_direct (LD, LD->N - rpos), x));
    tree_ext_large_t *node = new_tree_subnode_large (x, lrand48 (), MAKE_RPOS (rpos, TF_PLUS));
    *R = LARGE_NODE (tree_ext_insert (SMALL_NODE (*R), node->x, node->y, SMALL_NODE (node)));
    return node;
  } else {
    assert (NODE_TYPE(T) == TF_MINUS);
    T->rpos &= -4;	// TF_MINUS -> TF_ZERO
    assert (tree_ext_adjust_deltas (SMALL_NODE (*R), x, 1) == T);
    return LARGE_NODE (T);
  }
}