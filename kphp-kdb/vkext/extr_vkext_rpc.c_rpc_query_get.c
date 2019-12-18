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
struct rpc_query {long long qid; } ;

/* Variables and functions */
 long long RPC_QUERIES_MASK ; 
 long long first_qid ; 
 struct rpc_query* queries ; 

struct rpc_query *rpc_query_get (long long qid) {
  if (qid < first_qid) { return 0; }
  struct rpc_query *q = &queries[(qid - first_qid) & RPC_QUERIES_MASK];
  return q->qid == qid ? q : 0;
}