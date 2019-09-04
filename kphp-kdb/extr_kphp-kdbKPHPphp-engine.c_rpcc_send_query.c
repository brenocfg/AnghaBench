#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct connection {TYPE_1__* target; void* last_response_time; void* last_query_sent_time; } ;
struct conn_query {scalar_t__ req_generation; scalar_t__ extra; TYPE_2__* requester; } ;
struct TYPE_9__ {TYPE_3__* func; } ;
typedef  TYPE_4__ net_send_ansgen_t ;
typedef  int /*<<< orphan*/  net_ansgen_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* send_and_finish ) (TYPE_4__*,struct connection*) ;} ;
struct TYPE_7__ {scalar_t__ generation; int /*<<< orphan*/  queries_ok; } ;
struct TYPE_6__ {struct conn_query* first_query; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_conn_query (struct conn_query*) ; 
 int /*<<< orphan*/  dl_assert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pnet_query_answer (struct conn_query*) ; 
 int /*<<< orphan*/  pnet_query_delete (struct conn_query*) ; 
 void* precise_now ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,struct connection*) ; 
 int /*<<< orphan*/  zfree (struct conn_query*,int) ; 

int rpcc_send_query (struct connection *c) {
  //rpcc_ready
  c->last_query_sent_time = precise_now;
  c->last_response_time = precise_now;

  struct conn_query *q;
  dl_assert (c != NULL, "...");
  dl_assert (c->target != NULL, "...");

  while (c->target->first_query != (struct conn_query *)(c->target)) {
    q = c->target->first_query;
    dl_assert (q != NULL, "...");
    dl_assert (q->requester != NULL, "...");
    //    fprintf (stderr, "processing delayed query %p for target %p initiated by %p (%d:%d<=%d)\n", q, c->target, q->requester, q->requester->fd, q->req_generation, q->requester->generation);
    if (q->requester != NULL && q->requester->generation == q->req_generation) {
      q->requester->queries_ok++;
      //waiting_queries--;
      net_ansgen_t *net_ansgen = (net_ansgen_t *)q->extra;

      net_send_ansgen_t *ansgen = (net_send_ansgen_t *)net_ansgen;
      ansgen->func->send_and_finish (ansgen, c);

      pnet_query_answer (q);
      pnet_query_delete (q);
      break;
    } else {
      //waiting_queries--;
      delete_conn_query (q);
      zfree (q, sizeof (*q));
    }
  }
  return 0;
}