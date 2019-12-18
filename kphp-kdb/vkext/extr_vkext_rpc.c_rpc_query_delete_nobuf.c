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
struct rpc_query {scalar_t__ qid; int /*<<< orphan*/  (* extra_free ) (struct rpc_query*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  delete_query_from_queue (struct rpc_query*) ; 
 int /*<<< orphan*/  stub1 (struct rpc_query*) ; 
 int /*<<< orphan*/  total_working_qid ; 

__attribute__((used)) static void rpc_query_delete_nobuf (struct rpc_query *q) {
  //query_tree = tree_delete_query (query_tree, q);
  //zzfree (q, sizeof (*q));
  delete_query_from_queue (q);
  if (q->extra_free) {
    q->extra_free (q);    
  }
  q->qid = 0;
  total_working_qid --;
}