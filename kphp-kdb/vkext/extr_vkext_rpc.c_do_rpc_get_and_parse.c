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
struct rpc_query {double timeout; int /*<<< orphan*/  answer_len; int /*<<< orphan*/  answer; scalar_t__ start_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (struct rpc_query*) ; 
 scalar_t__ buffer_create_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ buffer_delete (scalar_t__) ; 
 scalar_t__ inbuf ; 
 int /*<<< orphan*/  rpc_get_and_parse ; 
 int rpc_get_answer (struct rpc_query*,double) ; 
 int /*<<< orphan*/  rpc_query_delete_nobuf (struct rpc_query*) ; 
 struct rpc_query* rpc_query_get (long long) ; 

int do_rpc_get_and_parse (long long qid, double timeout) { /* {{{ */
  ADD_CNT (rpc_get_and_parse);
  START_TIMER (rpc_get_and_parse);
  struct rpc_query *q = rpc_query_get (qid);
  if (!q) {
    END_TIMER (rpc_get_and_parse);
    return -1;
  }
  if (timeout >= 0) {
    timeout += q->start_time;
  } else {
    timeout = q->timeout;
  }
  int r = rpc_get_answer (q, timeout);
  //fetch_extra = q->extra;
  if (r < 0) {
    END_TIMER (rpc_get_and_parse);
    return -1;
  } else {
    if (inbuf) {
      inbuf = buffer_delete (inbuf);      
    }
    //struct rpc_query *q = rpc_query_get (qid);
    assert (q);
    inbuf = buffer_create_data (q->answer, q->answer_len);    
    rpc_query_delete_nobuf (q);    
    END_TIMER (rpc_get_and_parse);
    return 1;
  }
}