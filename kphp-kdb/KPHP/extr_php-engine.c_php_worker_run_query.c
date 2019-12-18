#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  php_worker ;
typedef  int /*<<< orphan*/  php_query_x2_t ;
typedef  int /*<<< orphan*/  php_query_rpc_message ;
typedef  int /*<<< orphan*/  php_query_rpc_answer ;
typedef  int /*<<< orphan*/  php_query_http_load_post_t ;
typedef  int /*<<< orphan*/  php_query_create_queue_t ;
typedef  int /*<<< orphan*/  php_query_connect_t ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ php_query_base_t ;
struct TYPE_5__ {char* desc; int /*<<< orphan*/  q_id; } ;

/* Variables and functions */
#define  PHPQ_CONNECT 134 
#define  PHPQ_CREATE_QUEUE 133 
#define  PHPQ_HTTP_LOAD_POST 132 
#define  PHPQ_NETQ 131 
#define  PHPQ_RPC_ANSWER 130 
#define  PHPQ_RPC_MESSAGE 129 
#define  PHPQ_X2 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_script ; 
 scalar_t__ php_script_get_query (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_worker_create_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_worker_http_load_post (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_worker_run_net_query (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  php_worker_run_query_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_worker_run_query_x2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_worker_run_rpc_answer_query (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_worker_run_rpc_send_message (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmem_free_ptrs () ; 
 TYPE_2__ query_stats ; 
 int /*<<< orphan*/  query_stats_id ; 

void php_worker_run_query (php_worker *worker) {
  php_query_base_t *q_base = (php_query_base_t *)php_script_get_query (php_script);

  qmem_free_ptrs();

  query_stats.q_id = query_stats_id;
  switch ((unsigned int)q_base->type & 0xFFFF0000) {
    case PHPQ_X2:
      query_stats.desc = "PHPQX2";
      php_worker_run_query_x2 (worker, (php_query_x2_t *)q_base);
      break;
    case PHPQ_RPC_ANSWER:
      query_stats.desc = "RPC_ANSWER";
      php_worker_run_rpc_answer_query (worker, (php_query_rpc_answer *)q_base);
      break;
    case PHPQ_RPC_MESSAGE:
      query_stats.desc = "RPC_SEND_MESSAGE";
      php_worker_run_rpc_send_message (worker, (php_query_rpc_message *)q_base);
      break;
    case PHPQ_CONNECT:
      query_stats.desc = "CONNECT";
      php_worker_run_query_connect (worker, (php_query_connect_t *)q_base);
      break;
    case PHPQ_NETQ:
      query_stats.desc = "NET";
      php_worker_run_net_query (worker, q_base);
      break;
    case PHPQ_CREATE_QUEUE:
      query_stats.desc = "CREATE_QUEUE";
      php_worker_create_queue (worker, (php_query_create_queue_t *)q_base);
      break;
    case PHPQ_HTTP_LOAD_POST:
      query_stats.desc = "HTTP_LOAD_POST";
      php_worker_http_load_post (worker, (php_query_http_load_post_t *)q_base);
      break;
    default:
      assert ("unknown php_query type" && 0);
  }
}