#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* topmsg_tree; } ;
typedef  TYPE_1__ user_t ;
struct TYPE_9__ {int x; struct TYPE_9__* right; int /*<<< orphan*/  data; struct TYPE_9__* left; } ;
typedef  TYPE_2__ tree_t ;
struct TYPE_10__ {int N; int* A; int last_A; int /*<<< orphan*/  root; } ;
typedef  TYPE_3__ listree_t ;
struct TYPE_11__ {int extra_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIL ; 
 TYPE_7__* UserHdr ; 
 int /*<<< orphan*/  assert (int) ; 
 int listree_get_kth_last (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lrand48 () ; 
 void* tree_num_insert (void*,int,int /*<<< orphan*/ ,int) ; 

int *rebuild_topmsg_tree (tree_t *T, int *L, int *LE, int max_peer_id, user_t *U, char *metafile) {
  int peer_id;
  listree_t X;
  if (T) {
    L = rebuild_topmsg_tree (T->left, L, LE, T->x - 1, U, metafile);
    peer_id = T->x;
    X.root = T->data;
    if (L < LE && L[1] == T->x) {
      X.N = ((L[2] - L[0]) >> 2);
      assert (L[0] >= 0 && L[0] <= L[2] && L[2] <= UserHdr->extra_offset);
      X.A = (int *) (metafile + L[0]);
      X.last_A = (X.N ? X.A[X.N-1] : 0);
      L += 2;
    } else {
      X.N = 0;
      X.A = 0;
      X.last_A = 0;
    }
    int local_id = listree_get_kth_last (&X, 0);
    if (local_id != -1) {
      assert (local_id > 0);
      U->topmsg_tree = tree_num_insert (U->topmsg_tree, local_id, lrand48(), peer_id);
    }
    L = rebuild_topmsg_tree (T->right, L, LE, max_peer_id, U, metafile);
  }
  while (L < LE && L[1] <= max_peer_id) {
    peer_id = L[1];
    X.root = NIL;
    X.N = ((L[2] - L[0]) >> 2);
    assert (L[0] >= 0 && L[0] <= L[2] && L[2] <= UserHdr->extra_offset);
    X.A = (int *) (metafile + L[0]);
    X.last_A = (X.N ? X.A[X.N-1] : 0);
    L += 2;
    int local_id = listree_get_kth_last (&X, 0);
    if (local_id != -1) {
      assert (local_id > 0);
      U->topmsg_tree = tree_num_insert (U->topmsg_tree, local_id, lrand48(), peer_id);
    }
  }
  return L;
}