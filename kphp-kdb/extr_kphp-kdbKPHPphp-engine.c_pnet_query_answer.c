#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct connection {scalar_t__ generation; int /*<<< orphan*/ * type; } ;
struct conn_query {scalar_t__ req_generation; scalar_t__ extra; struct connection* requester; } ;
struct TYPE_5__ {int /*<<< orphan*/  ans; } ;
typedef  TYPE_1__ net_ansgen_t ;
struct TYPE_8__ {void* extra; } ;
struct TYPE_7__ {void* extra; } ;
struct TYPE_6__ {void* extra; } ;

/* Variables and functions */
 TYPE_4__* HTS_DATA (struct connection*) ; 
 TYPE_3__* RPCC_DATA (struct connection*) ; 
 TYPE_2__* RPCS_DATA (struct connection*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ct_php_engine_http_server ; 
 int /*<<< orphan*/  ct_php_engine_rpc_server ; 
 int /*<<< orphan*/  ct_php_rpc_client ; 
 int /*<<< orphan*/  php_worker_answer_query (void*,int /*<<< orphan*/ ) ; 

void pnet_query_answer (struct conn_query *q) {
  struct connection *req = q->requester;
  if (req != NULL && req->generation == q->req_generation) {
    void *extra = NULL;
    if (req->type == &ct_php_engine_rpc_server) {
      extra = RPCS_DATA (req)->extra;
    } else if (req->type == &ct_php_rpc_client) {
      extra = RPCC_DATA (req)->extra;
    } else if (req->type == &ct_php_engine_http_server) {
      extra = HTS_DATA (req)->extra;
    } else {
      assert ("unexpected type of connection\n" && 0);
    }
    php_worker_answer_query (extra, ((net_ansgen_t *)(q->extra))->ans);
  }
}