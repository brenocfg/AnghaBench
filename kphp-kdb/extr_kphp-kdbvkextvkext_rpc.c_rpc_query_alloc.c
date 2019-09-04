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
struct rpc_query {size_t qid; double timeout; int /*<<< orphan*/  start_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 int RPC_MAX_QUERIES ; 
 size_t RPC_QUERIES_MASK ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 size_t first_qid ; 
 size_t last_qid ; 
 int max_query_id ; 
 int /*<<< orphan*/  memset (struct rpc_query*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  precise_now ; 
 struct rpc_query* queries ; 
 int /*<<< orphan*/  total_queries ; 
 int total_working_qid ; 
 int /*<<< orphan*/  tree_insert ; 
 int /*<<< orphan*/  update_precise_now () ; 

__attribute__((used)) static struct rpc_query *rpc_query_alloc (double timeout) {
  ADD_CNT (tree_insert);
  START_TIMER (tree_insert);
  if (total_working_qid > RPC_MAX_QUERIES / 2) {
    END_TIMER (tree_insert);
    return 0;
  }
  last_qid ++;
  while (queries[(last_qid - first_qid) & RPC_QUERIES_MASK].qid >= first_qid) { last_qid ++; }
  int fd = (last_qid - first_qid) & RPC_QUERIES_MASK;
  if (fd >= max_query_id) {
    max_query_id = fd + 1;
  }
  //long long qid = last_qid + 1;
  long long qid = last_qid;
  update_precise_now ();
  struct rpc_query *q = &queries[(qid - first_qid) & RPC_QUERIES_MASK];
  memset (q, 0, sizeof (*q));
  q->qid = qid;
  q->start_time = precise_now;
  q->timeout = timeout;
/*  ADD_CNT(tree_insert);
  START_TICKS(tree_insert);
  query_tree = tree_insert_query (query_tree, q, lrand48 ());
  END_TICKS(tree_insert);*/
  total_working_qid ++;
  total_queries ++;
  END_TIMER (tree_insert);
  return q;
}