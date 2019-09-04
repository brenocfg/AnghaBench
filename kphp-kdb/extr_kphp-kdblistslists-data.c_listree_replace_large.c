#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree_ext_small_t ;
struct TYPE_10__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ tree_ext_large_t ;
typedef  int /*<<< orphan*/  object_id_t ;
struct TYPE_11__ {scalar_t__ N; TYPE_1__** root; } ;
typedef  TYPE_2__ listree_direct_t ;

/* Variables and functions */
 TYPE_1__* LARGE_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAKE_RPOS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ NODE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SMALL_NODE (TYPE_1__*) ; 
 scalar_t__ TF_MINUS ; 
 int /*<<< orphan*/  TF_ZERO ; 
 int /*<<< orphan*/  assert (int) ; 
 int find_rpos_direct (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_data_direct (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  lrand48 () ; 
 TYPE_1__* new_tree_subnode_large (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ object_id_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tree_ext_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tree_ext_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree_ext_large_t *listree_replace_large (listree_direct_t *LD, object_id_t x) {
  tree_ext_large_t **R = LD->root;
  int rpos;
  tree_ext_small_t *T = tree_ext_lookup (SMALL_NODE (*R), x);
  if (T == NIL) {
    rpos = find_rpos_direct (LD, x);
    assert (rpos > 0 && object_id_equal (get_data_direct (LD, LD->N - rpos), x));
    tree_ext_large_t *node = new_tree_subnode_large (x, lrand48 (), MAKE_RPOS (rpos, TF_ZERO));
    *R = LARGE_NODE (tree_ext_insert (SMALL_NODE (*R), node->x, node->y, SMALL_NODE (node)));
    return node;
  } else {
    assert (NODE_TYPE (T) != TF_MINUS);
    return LARGE_NODE (T);
  }
}