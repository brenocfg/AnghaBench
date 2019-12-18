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
typedef  TYPE_1__ tree_ext_global_t ;
typedef  int /*<<< orphan*/  object_id_t ;
struct TYPE_19__ {scalar_t__ N; TYPE_1__** root; } ;
typedef  TYPE_2__ listree_global_t ;
typedef  scalar_t__ global_id_t ;

/* Variables and functions */
 TYPE_1__* DeletedSubnode_global ; 
 int /*<<< orphan*/  MAKE_RPOS (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* NILG ; 
 scalar_t__ NODE_TYPE (TYPE_1__*) ; 
 scalar_t__ TF_MINUS ; 
 int /*<<< orphan*/  TF_PLUS ; 
 int /*<<< orphan*/  assert (int) ; 
 int find_rpos_global (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  free_tree_ext_global_node (TYPE_1__*) ; 
 scalar_t__ get_data_global (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  lrand48 () ; 
 TYPE_1__* new_tree_subnode_global (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* tree_ext_global_delete (TYPE_1__*,scalar_t__) ; 
 TYPE_1__* tree_ext_global_insert (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* tree_ext_global_lookup (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void listree_insert_global (listree_global_t *LG, global_id_t x, object_id_t z) {
  tree_ext_global_t **R = LG->root;
  int rpos;
  tree_ext_global_t *T = tree_ext_global_lookup (*R, x);
  if (T == NILG) {
    rpos = find_rpos_global (LG, x);
    assert (!rpos || get_data_global (LG, LG->N - rpos) != x);
    tree_ext_global_t *node = new_tree_subnode_global (x, lrand48(), MAKE_RPOS (rpos, TF_PLUS), z);
    *R = tree_ext_global_insert (*R, node->x, node->y, node);
  } else {
    assert (NODE_TYPE(T) == TF_MINUS);
    DeletedSubnode_global = 0;
    *R = tree_ext_global_delete (*R, x);
    assert (DeletedSubnode_global == T);
    free_tree_ext_global_node (T);
  }
}