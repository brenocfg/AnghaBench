#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct secure_receive_answer {int answer_len; char* answer; int binlog; int /*<<< orphan*/  answer_op; int /*<<< orphan*/  pid; int /*<<< orphan*/  qid; int /*<<< orphan*/  binlog_pos; scalar_t__ h; } ;
struct rpc_query {int /*<<< orphan*/  pid; int /*<<< orphan*/  old_qid; } ;
struct lev_answer_tx {int answer_len; char* answer; int /*<<< orphan*/  op; int /*<<< orphan*/  pid; int /*<<< orphan*/  qid; } ;
struct TYPE_4__ {TYPE_1__* h; } ;
struct TYPE_3__ {int /*<<< orphan*/  real_op; } ;

/* Variables and functions */
 TYPE_2__* CQ ; 
 int /*<<< orphan*/  LEV_ANSWER_TX ; 
 int /*<<< orphan*/  RPC_FUN_NEXT ; 
 struct lev_answer_tx* alloc_log_event (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int binlog_mode_on ; 
 int /*<<< orphan*/  flush_cbinlog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_binlog_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_last_pos () ; 
 int /*<<< orphan*/  lrand48 () ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  secure_answer_allocated ; 
 int /*<<< orphan*/  secure_receive_answer_tree ; 
 int /*<<< orphan*/  tl_fetch_lookup_data (char*,int) ; 
 int tl_fetch_unread () ; 
 int tl_write_header (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  tree_insert_secure_receive_answer (int /*<<< orphan*/ ,struct secure_receive_answer*,int /*<<< orphan*/ ) ; 
 struct secure_receive_answer* zmalloc (int) ; 

int _secure_receive_on_answer (void **IP, void **Data, int binlog) {
  struct rpc_query *q = *Data;
  struct secure_receive_answer *A = zmalloc (sizeof (*A));
  A->qid = q->old_qid;
  A->pid = q->pid;
  //A->h = tl_query_header_dup (CQ->h);
  A->h = 0;
  static char buf[(1 << 17)];
  int r = tl_write_header (CQ->h, (int *)buf, (1 << 17));
  assert (r >= 0);
  A->answer_op = CQ->h->real_op;
  A->answer_len = tl_fetch_unread () + r;
  A->answer = malloc (A->answer_len);
  A->binlog = 0;
  memcpy (A->answer, buf, r);

  //int t = 
  tl_fetch_lookup_data (A->answer + r, A->answer_len - r);
  secure_receive_answer_tree = tree_insert_secure_receive_answer (secure_receive_answer_tree, A, lrand48 ());
  secure_answer_allocated ++;
  if (binlog) {
    A->binlog_pos  = log_last_pos ();
    insert_binlog_pos (A->binlog_pos, 0);
    struct lev_answer_tx *L = alloc_log_event (LEV_ANSWER_TX, sizeof (*L) + A->answer_len, 0);
    L->qid = A->qid;
    L->pid = A->pid;
    L->op = A->answer_op;
    L->answer_len = A->answer_len;
    memcpy (L->answer, A->answer, A->answer_len);
    A->binlog = 1;
    if (binlog_mode_on & 2) {
      flush_cbinlog (0);
    }
  }
  RPC_FUN_NEXT;
}