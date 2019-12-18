#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ tree_ext_small_t ;
struct TYPE_15__ {int /*<<< orphan*/  rpos; } ;
typedef  TYPE_2__ tree_ext_large_t ;
struct tree_payload {int /*<<< orphan*/  text; } ;
typedef  int /*<<< orphan*/  object_id_t ;
struct TYPE_16__ {scalar_t__ N; TYPE_2__** root; } ;
typedef  TYPE_3__ listree_direct_t ;

/* Variables and functions */
 scalar_t__ DeletedSubnode ; 
 TYPE_2__* LARGE_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKE_RPOS (int,int /*<<< orphan*/ ) ; 
 scalar_t__ NIL ; 
 int NODE_TYPE (TYPE_2__*) ; 
 struct tree_payload* PAYLOAD (TYPE_2__*) ; 
 scalar_t__ SMALL_NODE (TYPE_2__*) ; 
 int /*<<< orphan*/  TF_MINUS ; 
#define  TF_PLUS 129 
#define  TF_ZERO 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  empty_string ; 
 int find_rpos_direct (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_tree_ext_large_node (TYPE_2__*) ; 
 int /*<<< orphan*/  get_data_direct (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  get_text_data_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lrand48 () ; 
 TYPE_2__* new_tree_subnode_large (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ object_id_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_ext_adjust_deltas (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tree_ext_delete (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_ext_insert (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  tree_ext_lookup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void listree_delete_large (listree_direct_t *LD, object_id_t x) {
  tree_ext_large_t **R = LD->root;
  int rpos;
  tree_ext_large_t *T = LARGE_NODE (tree_ext_lookup (SMALL_NODE (*R), x));

  if (SMALL_NODE(T) == NIL) {
    rpos = find_rpos_direct (LD, x);
    assert (rpos > 0 && object_id_equal (get_data_direct (LD, LD->N - rpos), x));
    tree_ext_small_t *node = SMALL_NODE (new_tree_subnode_large (x, lrand48 (), MAKE_RPOS (rpos, TF_MINUS)));
    *R = LARGE_NODE (tree_ext_insert (SMALL_NODE (*R), node->x, node->y, node));
  } else {
    struct tree_payload *P;
    switch (NODE_TYPE(T)) {
//    case TF_REPLACED:
    case TF_ZERO:
      P = PAYLOAD (T);
      if (P->text) {
        if (P->text != empty_string) {
          zfree (P->text, get_text_data_len (P->text));
        }
        P->text = 0;
      }
      T->rpos |= TF_MINUS;	// execute recursive relax
      assert (tree_ext_adjust_deltas (SMALL_NODE (*R), x, -1) == SMALL_NODE(T));
      break;
    case TF_PLUS:
      DeletedSubnode = 0;
      *R = LARGE_NODE (tree_ext_delete (SMALL_NODE (*R), x));
      assert (DeletedSubnode == SMALL_NODE(T));
      free_tree_ext_large_node (T);
      break;
    default:
      assert (0);
    }
  }
}