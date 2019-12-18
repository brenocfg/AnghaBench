#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct secure_receive_answer {int answer_len; char* answer; int binlog; int /*<<< orphan*/  answer_op; int /*<<< orphan*/  pid; int /*<<< orphan*/  qid; int /*<<< orphan*/  binlog_pos; scalar_t__ h; } ;
struct rpc_query {scalar_t__ start_time; int /*<<< orphan*/  pid; int /*<<< orphan*/  old_qid; } ;
struct lev_answer_tx {int answer_len; char* answer; int /*<<< orphan*/  op; int /*<<< orphan*/  pid; int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_ANSWER_TX ; 
 int /*<<< orphan*/  RPC_FUN_NEXT ; 
 int /*<<< orphan*/  RPC_REQ_ERROR_WRAPPED ; 
 int TL_ERROR_QUERY_TIMEOUT ; 
 struct lev_answer_tx* alloc_log_event (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int binlog_mode_on ; 
 int /*<<< orphan*/  flush_cbinlog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_binlog_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_last_pos () ; 
 int /*<<< orphan*/  lrand48 () ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ precise_now ; 
 int /*<<< orphan*/  secure_answer_allocated ; 
 int /*<<< orphan*/  secure_receive_answer_tree ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tl_fetch_set_error (char*,int) ; 
 int /*<<< orphan*/  tree_insert_secure_receive_answer (int /*<<< orphan*/ ,struct secure_receive_answer*,int /*<<< orphan*/ ) ; 
 struct secure_receive_answer* zmalloc (int) ; 

int _secure_receive_on_alarm (void **IP, void **Data, int binlog) {
  struct rpc_query *q = *Data;
  struct secure_receive_answer *A = zmalloc (sizeof (*A));
  A->h = 0;
  A->qid = q->old_qid;
  A->pid = q->pid;
  A->answer_op = RPC_REQ_ERROR_WRAPPED;
  static char buf [1000];
  sprintf (buf + 1, "Query timeout: working_time = %lf", precise_now - q->start_time);
  tl_fetch_set_error (buf + 1, TL_ERROR_QUERY_TIMEOUT);
  int len = strlen (buf + 1) + 1;
  int pad = ((len + 3) & ~3) - len;
  memset (buf + len, 0, pad);
  buf[0] = len;
  len += pad;
  assert (len % 4 == 0);
  A->answer_len = 4 + len;
  A->answer = malloc (A->answer_len);
  A->binlog = 0;
  *(int *)A->answer = TL_ERROR_QUERY_TIMEOUT;
  memcpy (((char *)(A->answer)) + 4, buf, len);
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