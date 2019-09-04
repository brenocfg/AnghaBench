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
struct rpc_server {scalar_t__ sfd; scalar_t__ parse_status; int /*<<< orphan*/  parse_op; int /*<<< orphan*/  parse_len; int /*<<< orphan*/  parse_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_SKIP ; 
 scalar_t__ buffer_delete (scalar_t__) ; 
 scalar_t__ error_verbosity ; 
 int /*<<< orphan*/  free_connection ; 
 int /*<<< orphan*/  free_queries () ; 
 int /*<<< orphan*/  free_queue ; 
 scalar_t__ inbuf ; 
 int last_server_fd ; 
 scalar_t__ outbuf ; 
 scalar_t__ parse_status_reading_query ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  query_completed ; 
 int /*<<< orphan*/  queue_tree ; 
 int /*<<< orphan*/  rpc_connection_tree ; 
 int /*<<< orphan*/  rpc_prepare_stats (char*,int) ; 
 struct rpc_server** servers ; 
 int /*<<< orphan*/  tl_delete_old_configs () ; 
 int /*<<< orphan*/  tl_parse_on_rshutdown () ; 
 int /*<<< orphan*/  tree_act_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_act_qid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_act_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_clear_connection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_clear_qid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_clear_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_free_query ; 
 int /*<<< orphan*/  zzefree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rpc_on_rshutdown (int module_number) { /* {{{ */
  if (inbuf) {
    inbuf = buffer_delete (inbuf);
  }
  if (outbuf) {
    outbuf = buffer_delete (outbuf);
  }
  //tree_act_query (query_tree, rpc_query_free);
  //query_tree = tree_clear_query (query_tree);
  tree_act_qid (query_completed, try_free_query);
  //total_working_qid = 0;
  query_completed = tree_clear_qid (query_completed);
  
  int i;
  for (i = 0; i < last_server_fd; i++) {
    struct rpc_server *server = servers[i];
    if (server->sfd >= 0) {
      if (server->parse_status == parse_status_reading_query) {
        zzefree (server->parse_buf, server->parse_len);
        server->parse_op = RPC_SKIP;
      }
    }
  }

  tree_act_connection (rpc_connection_tree, free_connection);
  rpc_connection_tree = tree_clear_connection (rpc_connection_tree);

  tree_act_queue (queue_tree, free_queue);
  queue_tree = tree_clear_queue (queue_tree);
 
  free_queries ();
  tl_parse_on_rshutdown ();
  tl_delete_old_configs ();

#ifdef PRINT_DEBUG_INFO
  if (1) {
#else
  if (error_verbosity > 0) {
#endif
    static char buf[1000000];
    rpc_prepare_stats (buf, 1000000);
    printf ("%s", buf);
  }

  //fprintf (stderr, "send_noflush %lf clean %lf\n", stats.send_noflush_time, stats.clean_time);
}