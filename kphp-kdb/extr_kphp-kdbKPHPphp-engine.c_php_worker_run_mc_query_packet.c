#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_16__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
struct connection {scalar_t__ status; int /*<<< orphan*/ * Tmp; int /*<<< orphan*/  Out; } ;
struct conn_target {int /*<<< orphan*/  port; int /*<<< orphan*/  target; } ;
struct conn_query {int dummy; } ;
struct TYPE_21__ {TYPE_14__* conn; } ;
typedef  TYPE_3__ php_worker ;
typedef  int /*<<< orphan*/  php_query_base_t ;
struct TYPE_22__ {int extra_type; int connection_id; int /*<<< orphan*/  timeout; int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ php_net_query_packet_t ;
struct TYPE_23__ {TYPE_2__* func; } ;
typedef  TYPE_5__ net_ansgen_t ;
struct TYPE_24__ {TYPE_1__* func; } ;
typedef  TYPE_6__ mc_ansgen_t ;
struct TYPE_25__ {char* desc; int /*<<< orphan*/  port; int /*<<< orphan*/  query; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* set_desc ) (TYPE_5__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  (* set_query_type ) (TYPE_6__*,int) ;} ;
struct TYPE_18__ {int /*<<< orphan*/  (* flush_query ) (struct connection*) ;} ;
struct TYPE_17__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int MAX_TARGETS ; 
 TYPE_16__* MCC_FUNC (struct connection*) ; 
 int PNETF_IMMEDIATE ; 
 struct conn_target* Targets ; 
 int /*<<< orphan*/ * alloc_head_buffer () ; 
 scalar_t__ conn_connecting ; 
 int /*<<< orphan*/  conn_wait_net ; 
 struct conn_query* create_pnet_query (TYPE_14__*,struct connection*,TYPE_5__*,double) ; 
 double fix_timeout (int /*<<< orphan*/ ) ; 
 struct connection* get_target_connection_force (struct conn_target*) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 TYPE_6__* mc_ansgen_packet_create () ; 
 int /*<<< orphan*/  net_error (TYPE_5__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  php_script ; 
 int /*<<< orphan*/  php_script_query_readed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnet_query_timeout (struct conn_query*) ; 
 double precise_now ; 
 int /*<<< orphan*/  qmem_pstr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__ query_stats ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct connection*) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void php_worker_run_mc_query_packet (php_worker *worker, php_net_query_packet_t *query) {
  query_stats.desc = "MC";
  query_stats.query = query->data;

  php_script_query_readed (php_script);
  mc_ansgen_t *ansgen = mc_ansgen_packet_create();
  ansgen->func->set_query_type (ansgen, query->extra_type);

  net_ansgen_t *net_ansgen = (net_ansgen_t *)ansgen;
  int connection_id = query->connection_id;

  if (connection_id < 0 || connection_id >= MAX_TARGETS) {
    net_error (net_ansgen, (php_query_base_t *)query, "Invalid connection_id (1)");
    return;
  }

  struct conn_target *target = &Targets[connection_id];

  if (target == NULL) {
    net_error (net_ansgen, (php_query_base_t *)query, "Invalid connection_id (2)");
    return;
  }

  net_ansgen->func->set_desc (net_ansgen, qmem_pstr ("[%s:%d]", inet_ntoa (target->target), target->port));

  query_stats.port = target->port;

  struct connection *conn = get_target_connection_force (target);
  if (conn == NULL) {
    net_error (net_ansgen, (php_query_base_t *)query, "Failed to establish connection [probably reconnect timeout is not expired]");
    return;
  }

  if (conn->status != conn_connecting) {
    write_out (&conn->Out, query->data, query->data_len);
    MCC_FUNC (conn)->flush_query (conn);
  } else {
    if (conn->Tmp == NULL) {
      conn->Tmp = alloc_head_buffer();
    }
    write_out (conn->Tmp, query->data, query->data_len);
  }

  double timeout = fix_timeout (query->timeout) + precise_now;
  struct conn_query *cq = create_pnet_query (worker->conn, conn, (net_ansgen_t *)ansgen, timeout);

  if (query->extra_type & PNETF_IMMEDIATE) {
    pnet_query_timeout (cq);
  } else if (worker->conn != NULL) {
    worker->conn->status = conn_wait_net;
  }

  return;
}