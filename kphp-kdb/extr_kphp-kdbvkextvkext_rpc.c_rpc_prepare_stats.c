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

/* Variables and functions */
 int active_net_connections ; 
 int config_crc64 ; 
 int dynamic_tree_nodes ; 
 int errored_queries ; 
 int finished_queries ; 
 char* global_errnum ; 
 int global_error ; 
 int last_server_fd ; 
 int net_connections_fails ; 
 int persistent_tree_nodes ; 
 int /*<<< orphan*/  ping_timeout ; 
 scalar_t__ snprintf (char*,int,char*,int,int,int,int,int,int,int,char*,int,char*,int,int,int,int,int,int,int,int,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int timedout_queries ; 
 int tl_config_name ; 
 int tl_constructors ; 
 int tl_functions ; 
 int tl_types ; 
 char* total_queries ; 
 int total_ref_cnt ; 
 int /*<<< orphan*/  total_tl_working ; 
 double total_tree_nodes_existed ; 
 int total_working_qid ; 

int rpc_prepare_stats (char *buf, int max_len) { /* {{{ */
  int x = 0;
#ifdef DEBUG_TICKS  
  x += snprintf (buf + x, max_len, PRINT_STAT(utime));
  x += snprintf (buf + x, max_len, PRINT_STAT(write));
  x += snprintf (buf + x, max_len, PRINT_STAT(read));
  x += snprintf (buf + x, max_len, PRINT_STAT(force_read));
  x += snprintf (buf + x, max_len, PRINT_STAT(recv));
  x += snprintf (buf + x, max_len, PRINT_STAT(send));
  x += snprintf (buf + x, max_len, PRINT_STAT(poll));
  x += snprintf (buf + x, max_len, PRINT_STAT(read_in));
  x += snprintf (buf + x, max_len, PRINT_STAT(write_out));
  x += snprintf (buf + x, max_len, PRINT_STAT(rpc_read));
  x += snprintf (buf + x, max_len, PRINT_STAT(rpc_write));
  x += snprintf (buf + x, max_len, PRINT_STAT(rpc_write_handshake));
  x += snprintf (buf + x, max_len, PRINT_STAT(rpc_send));
  x += snprintf (buf + x, max_len, PRINT_STAT(rpc_flush));
  x += snprintf (buf + x, max_len, PRINT_STAT(rpc_get_answer));
  x += snprintf (buf + x, max_len, PRINT_STAT(rpc_get_and_parse));
  x += snprintf (buf + x, max_len, PRINT_STAT(rpc_get));
  x += snprintf (buf + x, max_len, PRINT_STAT(rpc_poll));
  x += snprintf (buf + x, max_len, PRINT_STAT(realloc));
  x += snprintf (buf + x, max_len, PRINT_STAT(emalloc));
  x += snprintf (buf + x, max_len, PRINT_STAT(tmp));
  x += snprintf (buf + x, max_len, PRINT_STAT(rpc_work));
  x += snprintf (buf + x, max_len, PRINT_STAT(rpc_sock_connect));
  x += snprintf (buf + x, max_len, PRINT_STAT(store));
  x += snprintf (buf + x, max_len, PRINT_STAT(fetch));
  x += snprintf (buf + x, max_len, PRINT_STAT(crc32));
  x += snprintf (buf + x, max_len, PRINT_STAT(tree_insert));
  x += snprintf (buf + x, max_len, PRINT_STAT(total));
  x += snprintf (buf + x, max_len, PRINT_STAT(malloc));
  x += snprintf (buf + x, max_len, PRINT_STAT(parse));
  x += snprintf (buf + x, max_len, PRINT_STAT(precise_now_updates));
  x += snprintf (buf + x, max_len, PRINT_STAT(connect));
  x += snprintf (buf + x, max_len, PRINT_STAT(get_field));
  x += snprintf (buf + x, max_len, PRINT_STAT(set_field));
  x += snprintf (buf + x, max_len, PRINT_STAT(minit));
#endif
#ifdef DEBUG_MEMORY
  x += snprintf (buf + x, max_len, "malloc %lld, emalloc %lld, rmalloc %lld, pmalloc %lld\n", stats.malloc, stats.emalloc, stats.rmalloc, stats.pmalloc);
#endif
  x += snprintf (buf + x, max_len, 
    "active_net_connections\t%d\n"
    "net_connections_fails\t%d\n"
    "total_net_connections\t%d\n"
    "active_queries\t%d\n"
    "finished_queries\t%d\n"
    "errored_queries\t%d\n"
    "timedout_queries\t%d\n"
    "total_queries\t%lld\n"
    "last_error\t%s\n"
    "last_error_code\t%d\n"
    "tl_config_file\t%s\n"
    "tl_config_crc64\t0x%llx\n"
    "tl_functions\t%d\n"
    "tl_constructors\t%d\n"
    "tl_types\t%d\n"
    "persistent_tree_nodes\t%d\n"
    "dynamic_tree_nodes\t%d\n"
    "total_ref_cnt\t%d\n"
    "total_tree_nodes_existed\t%d\n"
    "total_tl_working\t%d\n"
    "ping_timeout\t%0.3f\n"
    ,
    active_net_connections,
    net_connections_fails,
    last_server_fd,
    total_working_qid,
    finished_queries,
    errored_queries,
    timedout_queries,
    total_queries,
    global_error,
    global_errnum,
    tl_config_name,
    config_crc64,
    tl_functions,
    tl_constructors,
    tl_types,
    persistent_tree_nodes,
    dynamic_tree_nodes,
    total_ref_cnt,
    total_tree_nodes_existed,
    total_tl_working,
    ping_timeout
    );
  return x;
}