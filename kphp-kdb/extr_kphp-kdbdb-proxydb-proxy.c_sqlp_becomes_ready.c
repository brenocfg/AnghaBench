#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connection {TYPE_1__* target; } ;
struct conn_query {scalar_t__ req_generation; TYPE_2__* requester; } ;
struct TYPE_4__ {scalar_t__ generation; int /*<<< orphan*/  queries_ok; } ;
struct TYPE_3__ {struct conn_query* first_query; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_conn_query (struct conn_query*) ; 
 int /*<<< orphan*/  waiting_queries ; 
 int /*<<< orphan*/  zfree (struct conn_query*,int) ; 

int sqlp_becomes_ready (struct connection *c) {
  struct conn_query *q;

  while (c->target->first_query != (struct conn_query *)(c->target)) {
    q = c->target->first_query;
    //    fprintf (stderr, "processing delayed query %p for target %p initiated by %p (%d:%d<=%d)\n", q, c->target, q->requester, q->requester->fd, q->req_generation, q->requester->generation);
    if (q->requester->generation == q->req_generation) {
      // q->requester->status = conn_expect_query;   // !!NOT SURE THAT THIS CAN BE COMMENTED!!
      q->requester->queries_ok++;
      waiting_queries--;
      delete_conn_query (q);
      zfree (q, sizeof (*q));
      break;
    } else {
      waiting_queries--;
      delete_conn_query (q);
      zfree (q, sizeof (*q));
    }
  }
  return 0;
}