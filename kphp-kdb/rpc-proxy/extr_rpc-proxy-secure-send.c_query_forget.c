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
struct secure_send_extra {int /*<<< orphan*/  binlog_pos; } ;
struct rpc_query {struct secure_send_extra* extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_binlog_pos (int /*<<< orphan*/ ,int) ; 
 struct rpc_query* get_rpc_query (long long) ; 
 int /*<<< orphan*/  query_on_free (struct rpc_query*) ; 

void query_forget (long long qid) {
  struct rpc_query *q = get_rpc_query (qid);    
  if (!q) { return; }
  struct secure_send_extra *E = q->extra;
  delete_binlog_pos (E->binlog_pos, 1);
  query_on_free (q);
}