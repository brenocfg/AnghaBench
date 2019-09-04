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
struct tree_secure_receive_answer {struct secure_receive_answer* x; } ;
struct process_id {int dummy; } ;
struct secure_receive_answer {long long qid; int /*<<< orphan*/  binlog_pos; scalar_t__ h; int /*<<< orphan*/  answer; struct process_id pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_binlog_pos (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secure_answer_allocated ; 
 int /*<<< orphan*/  secure_receive_answer_tree ; 
 int /*<<< orphan*/  tl_query_header_delete (scalar_t__) ; 
 int /*<<< orphan*/  tree_delete_secure_receive_answer (int /*<<< orphan*/ ,struct secure_receive_answer*) ; 
 struct tree_secure_receive_answer* tree_lookup_secure_receive_answer (int /*<<< orphan*/ ,struct secure_receive_answer*) ; 
 int /*<<< orphan*/  zfree (struct secure_receive_answer*,int) ; 

void answer_forget (long long qid, struct process_id *pid) {
  struct secure_receive_answer t;
  t.qid = qid;
  t.pid = *pid;
  struct tree_secure_receive_answer *T = tree_lookup_secure_receive_answer (secure_receive_answer_tree, &t);
  if (T) {
    secure_receive_answer_tree = tree_delete_secure_receive_answer (secure_receive_answer_tree, T->x);
    struct secure_receive_answer *A = T->x;
    secure_answer_allocated --;
    free (A->answer);
    if (A->h) {
      tl_query_header_delete (A->h);
    }
    delete_binlog_pos (A->binlog_pos, 1);
    zfree (A, sizeof (*A));
  }
}