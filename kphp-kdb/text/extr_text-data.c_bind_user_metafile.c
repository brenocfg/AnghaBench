#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {int dir_entry; int user_id; scalar_t__ topmsg_tree; scalar_t__ delayed_value_tree; scalar_t__ delayed_tree; int /*<<< orphan*/  peer_tree; TYPE_1__* Sublists; TYPE_3__* mf; } ;
typedef  TYPE_2__ user_t ;
struct TYPE_14__ {char* data; scalar_t__ len; int /*<<< orphan*/  aio; } ;
typedef  TYPE_3__ core_mf_t ;
struct TYPE_15__ {int combined_xor_and; } ;
struct TYPE_12__ {int N; int* A; int last_A; } ;
struct TYPE_11__ {int sublists_num; int sublists_offset; scalar_t__ legacy_list_offset; int peers_offset; int peers_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PEER_ID ; 
 scalar_t__ NIL_N ; 
 TYPE_10__* UserHdr ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,TYPE_2__*,int,char*) ; 
 TYPE_7__* idx_Sublists_packed ; 
 int /*<<< orphan*/  process_delayed_ops (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  process_delayed_values (TYPE_2__*,scalar_t__) ; 
 int* rebuild_topmsg_tree (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int sublists_num ; 
 int verbosity ; 

void bind_user_metafile (user_t *U) {
  core_mf_t *M = U->mf;
  int i, *x;
  assert (M && !M->aio);
  char *metafile = M->data;
  assert (U->dir_entry);
  assert (UserHdr->sublists_num == sublists_num);

  if (verbosity > 2) {
    fprintf (stderr, "bind_user_metafile(%p) : user_id=%d mf=%p\n", U, U->user_id, metafile);
  }

  x = (int *) (metafile + UserHdr->sublists_offset);
  assert (!x[0]);
  for (i = 0; i < sublists_num; i++) {
    int *A = (int *) (metafile + UserHdr->sublists_offset + sublists_num * 8 + 4) + x[2*i];
    int N = x[2*i+2] - x[2*i];
    assert (x[2*i+1] == idx_Sublists_packed[i].combined_xor_and);
    assert (N >= 0);
    assert (N == U->Sublists[i].N);
    assert (!U->Sublists[i].A);
    U->Sublists[i].A = A;
    assert (!N || A[N-1] <= U->Sublists[i].last_A);
    U->Sublists[i].last_A = N ? A[N-1] : 0;
  }
  assert (UserHdr->sublists_offset + sublists_num * 8 + 4 + x[2*i] * 4 <= UserHdr->legacy_list_offset && UserHdr->legacy_list_offset <= M->len);

  assert (U->topmsg_tree == NIL_N);

  int *L = (int *) (metafile + UserHdr->peers_offset);
  int *LE = L + 2 * UserHdr->peers_num;

  assert (rebuild_topmsg_tree (U->peer_tree, L, LE, MAX_PEER_ID, U, metafile) == LE);

  if (U->delayed_tree) {
    /* perform delayed operations */
    process_delayed_ops (U, U->delayed_tree);
    U->delayed_tree = 0;
  }

  if (U->delayed_value_tree) {
    process_delayed_values (U, U->delayed_value_tree);
    U->delayed_value_tree = 0;
  }

}