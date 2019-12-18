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
struct process_id {int dummy; } ;
struct secure_receive_answer {long long qid; int answer_op; int binlog; int answer_len; int /*<<< orphan*/  binlog_pos; int /*<<< orphan*/  answer; struct process_id pid; scalar_t__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  insert_binlog_pos (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_cur_pos () ; 
 int /*<<< orphan*/  lrand48 () ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  secure_answer_allocated ; 
 int /*<<< orphan*/  secure_receive_answer_tree ; 
 int /*<<< orphan*/  tree_insert_secure_receive_answer (int /*<<< orphan*/ ,struct secure_receive_answer*,int /*<<< orphan*/ ) ; 
 struct secure_receive_answer* zmalloc (int) ; 

void answer_tx (long long qid, struct process_id *pid, int op, int answer_len, int *answer) {
  struct secure_receive_answer *A = zmalloc (sizeof (*A));
  A->h = 0;
  A->qid = qid;
  A->pid = *pid;
  A->answer_op = op;
  A->binlog = 1;
  A->answer_len = answer_len;
  A->answer = malloc (A->answer_len);
  memcpy (A->answer, answer, answer_len);
  secure_receive_answer_tree = tree_insert_secure_receive_answer (secure_receive_answer_tree, A, lrand48 ());
  secure_answer_allocated ++;
  insert_binlog_pos (log_cur_pos (), 1);
  A->binlog_pos = log_cur_pos ();
}