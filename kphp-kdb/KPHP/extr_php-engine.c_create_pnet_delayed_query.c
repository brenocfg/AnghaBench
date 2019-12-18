#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct connection {int dummy; } ;
struct conn_target {int dummy; } ;
struct TYPE_2__ {double wakeup_time; } ;
struct conn_query {TYPE_1__ timer; int /*<<< orphan*/ * cq_type; int /*<<< orphan*/ * extra; int /*<<< orphan*/  start_time; struct connection* requester; scalar_t__ custom_type; } ;
typedef  int /*<<< orphan*/  net_ansgen_t ;

/* Variables and functions */
 int /*<<< orphan*/  insert_conn_query_into_list (struct conn_query*,struct conn_query*) ; 
 int /*<<< orphan*/  pnet_delayed_cq_func ; 
 int /*<<< orphan*/  precise_now ; 
 struct conn_query* zmalloc (int) ; 

void create_pnet_delayed_query (struct connection *http_conn, struct conn_target *t, net_ansgen_t *gen, double finish_time) {
  struct conn_query *q = zmalloc (sizeof (struct conn_query));

  q->custom_type = 0;
  //q->outbound = conn;
  q->requester = http_conn;
  q->start_time = precise_now;

  q->extra = gen;

  q->cq_type = &pnet_delayed_cq_func;
  q->timer.wakeup_time = finish_time;

  insert_conn_query_into_list (q, (struct conn_query *)t);

  return;
}