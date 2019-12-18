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
struct rpc_query {int status; int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 int /*<<< orphan*/  END_TIMER (int (*) (struct rpc_query*,double)) ; 
 int /*<<< orphan*/  START_TIMER (int (*) (struct rpc_query*,double)) ; 
 double precise_now ; 
 int /*<<< orphan*/  query_completed ; 
#define  query_status_error 132 
#define  query_status_ok 131 
#define  query_status_receiving 130 
#define  query_status_running 129 
#define  query_status_sent 128 
 int /*<<< orphan*/  rpc_poll (double) ; 
 int /*<<< orphan*/  rpc_query_delete (struct rpc_query*) ; 
 int /*<<< orphan*/  timedout_queries ; 
 int /*<<< orphan*/  tree_delete_qid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_precise_now () ; 

__attribute__((used)) static int rpc_get_answer (struct rpc_query *q, double timeout) { /* {{{ */
  if (!q) {
    //fprintf (stderr, "Can not find query with id %lld\n", q->qid);
    return -1;
  }
  START_TIMER (rpc_get_answer);
  update_precise_now ();
  while (timeout > precise_now && (q->status == query_status_sent || q->status == query_status_running || q->status == query_status_receiving)) {
    rpc_poll (timeout);
    update_precise_now ();
  }
  switch (q->status) {
  case query_status_sent:
  case query_status_running:
  case query_status_receiving:
    rpc_query_delete (q);
    timedout_queries ++;
    END_TIMER (rpc_get_answer);
    return -1;
  case query_status_ok:
    query_completed = tree_delete_qid (query_completed, q->qid);
    END_TIMER (rpc_get_answer);
    return 1;
  case query_status_error:
    query_completed = tree_delete_qid (query_completed, q->qid);
    rpc_query_delete (q);
    END_TIMER (rpc_get_answer);
    return -1;
  }
  END_TIMER (rpc_get_answer);
  return 0;
}