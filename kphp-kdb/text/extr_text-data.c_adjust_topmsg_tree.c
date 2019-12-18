#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int user_id; void* topmsg_tree; int /*<<< orphan*/  peer_tree; struct file_user_list_entry* dir_entry; } ;
typedef  TYPE_1__ user_t ;
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ tree_t ;
struct TYPE_14__ {int z; int x; } ;
typedef  TYPE_3__ tree_num_t ;
struct file_user_list_entry {int user_last_local_id; } ;
struct TYPE_15__ {int N; int /*<<< orphan*/  last_A; int /*<<< orphan*/ * A; int /*<<< orphan*/  root; } ;
typedef  TYPE_4__ listree_t ;

/* Variables and functions */
 int /*<<< orphan*/  NIL ; 
 void* NIL_N ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fetch_file_peer_list (char*,int,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,TYPE_1__*,char*,struct file_user_list_entry*,int,int,int,int,int,int,int) ; 
 char* get_user_metafile (TYPE_1__*) ; 
 int listree_get_kth_last (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lrand48 () ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_2__* tree_lookup (int /*<<< orphan*/ ,int) ; 
 void* tree_num_delete (void*,int) ; 
 void* tree_num_insert (void*,int,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* tree_num_lookup (void*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,TYPE_1__*,int,int,int,int,int,char*,struct file_user_list_entry*) ; 

int adjust_topmsg_tree (user_t *U, int peer_id, int local_id, int op) {
  char *metafile = get_user_metafile (U);
  struct file_user_list_entry *D = U->dir_entry;
  listree_t X;
  int prev_id = 0;
  tree_num_t *TT;

  assert (local_id > 0 && (metafile || !D || local_id > D->user_last_local_id));

  if (!metafile && D) {
    assert (U->topmsg_tree == NIL_N);
    return 0;
  }

  tree_t *T = tree_lookup (U->peer_tree, peer_id);

  X.root = (T ? T->data : NIL);

  if (metafile) {
    X.A = fetch_file_peer_list (metafile, peer_id, &X.N);
    X.last_A = (X.N ? X.A[X.N-1] : 0);
    //fprintf (stderr, "peer list size %d: %d %d %d...", X.N, X.A?X.A[0]:-1, X.A?X.A[1]:-1, X.A?X.A[2]:-1);
  } else {
    X.A = 0;
    X.N = 0;
    X.last_A = 0;
  }

  prev_id = listree_get_kth_last (&X, 0);

  vkprintf (4, "adjust_topmsg_tree (%p %d, %d, %d, %d) : prev_id=%d metafile=%p D=%p\n", U, U->user_id, peer_id, local_id, op, prev_id, metafile, D);

  assert (prev_id == -1 || prev_id > 0);

  if (local_id < prev_id) {
    // we are inserting or deleting a message under current top of this peermsglistree
    return prev_id;
  }

  if (op > 0) {
    if (prev_id > 0) {
      TT = tree_num_lookup (U->topmsg_tree, prev_id);
      if (TT->z != peer_id) {
        fprintf (stderr, "ERROR in adjust_topmsg_tree: uid=%d, U=%p, mf=%p, D=%p, mf_last_local_id=%d, peer=%d, local_id=%d, prev_id=%d, op=%d, TT.x=%d, TT.z=%d\n", U->user_id, U, metafile, D, D ? D->user_last_local_id : 0, peer_id, local_id, prev_id, op, TT->x, TT->z);
	// print_backtrace ();
	// return 0;
      }
      assert (TT->z == peer_id);
      U->topmsg_tree = tree_num_delete (U->topmsg_tree, prev_id);
    }
    U->topmsg_tree = tree_num_insert (U->topmsg_tree, local_id, lrand48(), peer_id);
  } else {
    TT = tree_num_lookup (U->topmsg_tree, local_id);
    if (TT->z != peer_id) {
      fprintf (stderr, "ERROR in adjust_topmsg_tree: uid=%d, U=%p, mf=%p, D=%p, mf_last_local_id=%d, peer=%d, local_id=%d, prev_id=%d, op=%d, TT.x=%d, TT.z=%d\n", U->user_id, U, metafile, D, D ? D->user_last_local_id : 0, peer_id, local_id, prev_id, op, TT->x, TT->z);
      // print_backtrace ();
      // return 0;
    }
    assert (TT->z == peer_id);
    U->topmsg_tree = tree_num_delete (U->topmsg_tree, local_id);
    if (prev_id > 0) {
      U->topmsg_tree = tree_num_insert (U->topmsg_tree, prev_id, lrand48(), peer_id);
    }
  }

  return prev_id;
}