#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_result ;
struct TYPE_8__ {int paused; TYPE_7__* conn; int /*<<< orphan*/  req_id; scalar_t__ terminate_flag; void* state; int /*<<< orphan*/  mode; int /*<<< orphan*/  error_message; } ;
typedef  TYPE_1__ php_worker ;
struct TYPE_10__ {int /*<<< orphan*/  status; int /*<<< orphan*/  ev; } ;
struct TYPE_9__ {int is_wait_net; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  conn_wait_net ; 
 int epoll_fetch_events (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_utime_monotonic () ; 
 int /*<<< orphan*/  http_return (TYPE_7__*,char*,int) ; 
 int /*<<< orphan*/  http_worker ; 
 TYPE_6__ immediate_stats ; 
 int /*<<< orphan*/  php_script ; 
 int /*<<< orphan*/  php_script_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_script_get_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * php_script_get_res (int /*<<< orphan*/ ) ; 
 int php_script_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_script_iterate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_script_terminate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_worker_run_query (TYPE_1__*) ; 
 int /*<<< orphan*/  php_worker_set_result (TYPE_1__*,int /*<<< orphan*/ *) ; 
 void* phpq_free_script ; 
 int /*<<< orphan*/  put_event_into_heap_tail (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rpc_error (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_stored ; 
 int /*<<< orphan*/  rpc_worker ; 
#define  rst_error 132 
#define  rst_finished 131 
#define  rst_query 130 
#define  rst_query_running 129 
#define  rst_ready 128 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ) ; 

void php_worker_run (php_worker *worker) {
  int f = 1;
  while (f) {
    if (worker->terminate_flag) {
      php_script_terminate (php_script, worker->error_message);
    }

    get_utime_monotonic();
//    fprintf (stderr, "state = %d, f = %d\n", php_script_get_state (php_script), f);
    switch (php_script_get_state (php_script)) {
      case rst_ready: {
        vkprintf (2, "before php_script_iterate [req_id = %016llx] (before swap context)\n", worker->req_id);
        immediate_stats.is_wait_net = 0;
        php_script_iterate (php_script);
        vkprintf (2, "after php_script_iterate [req_id = %016llx] (after swap context)\n", worker->req_id);
        break;
      }
      case rst_query: {
        vkprintf (2, "got query [req_id = %016llx]\n", worker->req_id);
        php_worker_run_query (worker);
        break;
      }
      case rst_query_running: {
        vkprintf (2, "paused due to query [req_id = %016llx]\n", worker->req_id);
        f = 0;
        worker->paused = 1;
        immediate_stats.is_wait_net = 1;
        break;
      }
      case rst_error: {
        vkprintf (2, "php script [req_id = %016llx]: ERROR (probably timeout)\n", worker->req_id);
        php_script_finish (php_script);

        if (worker->conn != NULL) {
          if (worker->mode == http_worker) {
            http_return (worker->conn, "ERROR", 5);
          } else if (worker->mode == rpc_worker) {
            if (!rpc_stored) {
              rpc_error (worker, -504, php_script_get_error (php_script));
            }
          }
        }

        worker->state = phpq_free_script;
        f = 0;
        break;
      }
      case rst_finished: {
        vkprintf (2, "php script [req_id = %016llx]: OK (still can return RPC_ERROR)\n", worker->req_id);
        script_result *res = php_script_get_res (php_script);

        php_worker_set_result (worker, res);

        php_script_finish (php_script);


        worker->state = phpq_free_script;
        f = 0;
        break;
      }
      default:
        assert ("php_worker_run: unexpected state" && 0);
    }

    //trying to work with net
    if (!worker->terminate_flag) {
      int new_net_events_cnt = epoll_fetch_events (0);
      if (new_net_events_cnt > 0) {
        vkprintf (2, "paused for some net activity [req_id = %016llx]\n", worker->req_id);
        f = 0;
        put_event_into_heap_tail (worker->conn->ev, 1);
        worker->conn->status = conn_wait_net;
        worker->paused = 1;
      }
    }
  }
}