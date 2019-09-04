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
struct results_queue_entry {scalar_t__ binlog_pos; int /*<<< orphan*/  result; int /*<<< orphan*/  transaction_id; } ;
struct copyexec_rpc_send_data {scalar_t__ binlog_pos; int /*<<< orphan*/  result; int /*<<< orphan*/  transaction_id; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPYEXEC_RPC_TYPE_SEND_DATA ; 
 int /*<<< orphan*/  Q ; 
 int /*<<< orphan*/  cur_client_state ; 
 int /*<<< orphan*/  data_sent_time ; 
 scalar_t__ handshake_log_pos ; 
 int /*<<< orphan*/  now ; 
 struct results_queue_entry* results_queue_front () ; 
 int /*<<< orphan*/  results_queue_pop () ; 
 struct copyexec_rpc_send_data* rpc_create_query (int /*<<< orphan*/ ,int,struct connection*,int /*<<< orphan*/ ) ; 
 int rpc_send_query (int /*<<< orphan*/ ,struct connection*) ; 
 int /*<<< orphan*/  st_data_sent ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

int rpc_send_data (struct connection *c) {
  for (;;) {
    struct results_queue_entry *A = results_queue_front ();
    if (A == NULL) {
      vkprintf (3, "rpc_send_data: results_queue is empty.\n");
      return 0;
    }
    vkprintf (3, "rpc_send_data: A->pos: 0x%llx, A->transaction_id: %d, A->result:%x\n", A->binlog_pos, A->transaction_id, A->result);
    if (A->binlog_pos <= handshake_log_pos) {
      vkprintf (3, "rpc_send_data: Skipping sending A (handshake_log_pos: %lld)\n", handshake_log_pos);
      results_queue_pop ();
      continue;
    }
    struct copyexec_rpc_send_data *E = rpc_create_query (Q, sizeof (*E), c, COPYEXEC_RPC_TYPE_SEND_DATA);
    if (E == NULL) {
      vkprintf (2, "rpc_send_data: rpc_create_query returns NULL.\n");
      return -__LINE__;
    }
    E->binlog_pos = A->binlog_pos;
    E->transaction_id = A->transaction_id;
    E->result = A->result;
    vkprintf (3, "rpc_send_data: E->binlog_pos: 0x%llx, E->transaction_id: %d, E->result:%x\n", E->binlog_pos, E->transaction_id, E->result);
    cur_client_state = st_data_sent;
    data_sent_time = now;
    return rpc_send_query (Q, c);
  }
  return 0;
}