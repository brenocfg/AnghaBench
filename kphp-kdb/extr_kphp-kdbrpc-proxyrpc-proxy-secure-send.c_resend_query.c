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
struct secure_send_extra {int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; } ;
struct rpc_query {struct secure_send_extra* extra; int /*<<< orphan*/  qid; } ;
struct process_id {int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_INVOKE_REQ ; 
 int /*<<< orphan*/  resent_queries ; 
 struct connection* rpc_target_choose_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_target_lookup_hp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_end_ext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_init (struct connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_raw_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void resend_query (struct rpc_query *q, struct process_id *pid) {
  resent_queries ++;
  struct connection *d = rpc_target_choose_connection (rpc_target_lookup_hp (pid->ip, pid->port), 0);
  if (!d) { return; }
  tl_store_init (d, q->qid);
  struct secure_send_extra *E = q->extra;
  tl_store_raw_data (E->data, E->data_size);
  tl_store_end_ext (RPC_INVOKE_REQ);
}