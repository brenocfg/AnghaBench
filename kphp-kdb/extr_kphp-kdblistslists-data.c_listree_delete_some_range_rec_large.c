#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree_ext_small_t ;
struct TYPE_13__ {int y; scalar_t__ rpos; int /*<<< orphan*/  x; struct TYPE_13__* right; struct TYPE_13__* left; } ;
typedef  TYPE_1__ tree_ext_large_t ;
struct tree_payload {scalar_t__ text; } ;
typedef  int /*<<< orphan*/  listree_t ;
struct TYPE_14__ {int N; int /*<<< orphan*/  A; } ;
typedef  TYPE_2__ listree_direct_t ;

/* Variables and functions */
 TYPE_1__* LARGE_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKE_RPOS (int,scalar_t__) ; 
 scalar_t__ NIL ; 
 int NODE_RPOS (TYPE_1__*) ; 
 scalar_t__ NODE_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  OARR_ENTRY (int /*<<< orphan*/ ,int) ; 
 struct tree_payload* PAYLOAD (TYPE_1__*) ; 
 scalar_t__ SMALL_NODE (TYPE_1__*) ; 
 scalar_t__ TF_MINUS ; 
 scalar_t__ TF_PLUS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ empty_string ; 
 int /*<<< orphan*/  free_tree_ext_large_node (TYPE_1__*) ; 
 int /*<<< orphan*/  get_text_data_len (scalar_t__) ; 
 int /*<<< orphan*/  in_array (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  in_tree (scalar_t__) ; 
 int lrand48 () ; 
 TYPE_1__* new_tree_subnode_large (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_ext_merge (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tree_ext_relax (scalar_t__) ; 
 int /*<<< orphan*/  tree_ext_split (int /*<<< orphan*/ **,int /*<<< orphan*/ **,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree_ext_large_t *listree_delete_some_range_rec_large (tree_ext_large_t **R, listree_direct_t *LD, int a, int b, int last_y) {
  tree_ext_large_t *MN;
  if (SMALL_NODE (*R) == NIL) {
    int y;
    while (a <= b) {
      if (!in_array ((listree_t *)LD, a)) {
        // current_minus_node (aka MN) is created ONLY here, when we want to delete a pure array entry
        MN = new_tree_subnode_large (OARR_ENTRY (LD->A, a), y = lrand48 (), MAKE_RPOS (LD->N - a, TF_MINUS));
        if (y > last_y) {
          return MN;
        }
        *R = MN;
        tree_ext_relax (SMALL_NODE (*R));
        break;
      }
      a++;
    }
    if (SMALL_NODE (*R) == NIL) {
      return 0;
    }
  }

  tree_ext_large_t *T = *R;

  int N = LD->N; 
  int c = N - NODE_RPOS(T);		// # of array elements < T->x, i.e. A[0]...A[c-1]
  int lr = c - 1;			// left subtree corresponds to [a .. c-1]
  int rl = c + (NODE_TYPE(T) != TF_PLUS);	// right subtree corresponds to [rl .. b]

  assert (rl <= b + 1);

  MN = listree_delete_some_range_rec_large (&T->left, LD, a, lr, T->y);
  if (MN) {
    if (MN->y > last_y) {
      tree_ext_relax (SMALL_NODE (T));
      return MN;
    }
    tree_ext_split ((tree_ext_small_t **) &MN->left, (tree_ext_small_t **) &MN->right, SMALL_NODE (T), MN->x);
    *R = T = MN;
    tree_ext_relax (SMALL_NODE (T));
    c = N - NODE_RPOS(T);
    rl = c + 1; 
  }

  // now all listree elements up to T=*R have been processed, T and everything after haven't
  // c and rl are correct

  int delete_this = 0;

  if (NODE_TYPE(T) != TF_MINUS && !in_tree (SMALL_NODE (T))) {
    if (NODE_TYPE (T) == TF_PLUS) {
      delete_this = 1;
    } else {
      struct tree_payload *P = PAYLOAD (T);
      if (P->text) {
        if (P->text != empty_string) {
          zfree (P->text, get_text_data_len (P->text));
        }
        P->text = 0;
      }
      T->rpos |= TF_MINUS;
    }
    // T has to be relaxed afterwards, either by tree_ext_relax or by deleting
  }

  // here T itself has been processed, but its (possible) deletion has been delayed
  // we have to process the remainder to the right of T

  while (1) {
    MN = listree_delete_some_range_rec_large (&T->right, LD, rl, b, T->y); 
    if (delete_this) {
      *R = LARGE_NODE (tree_ext_merge (SMALL_NODE (T->left), SMALL_NODE(T->right)));
      free_tree_ext_large_node (T);
      T = *R;
      delete_this = 0;
    } else {
      tree_ext_relax (SMALL_NODE (T));
    }
    if (!MN || MN->y > last_y) {
      return MN;
    }
    tree_ext_split ((tree_ext_small_t **) &MN->left, (tree_ext_small_t **) &MN->right, SMALL_NODE (T), MN->x);
    *R = T = MN;
    tree_ext_relax (SMALL_NODE (T));
    c = N - NODE_RPOS(T);
    assert (c >= rl);
    rl = c + 1;
  }
}