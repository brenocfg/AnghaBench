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
struct connection {scalar_t__ generation; int queries_ok; int unreliability; struct conn_query* first_query; } ;
struct conn_query {scalar_t__ req_generation; struct connection* requester; } ;
struct TYPE_2__ {int /*<<< orphan*/  complete_count; } ;

/* Variables and functions */
 TYPE_1__* MCS_DATA (struct connection*) ; 
 int /*<<< orphan*/  active_queries ; 
 int /*<<< orphan*/  assert (struct connection*) ; 
 int /*<<< orphan*/  delete_conn_query (struct conn_query*) ; 
 int /*<<< orphan*/  zfree (struct conn_query*,int) ; 

int query_complete (struct connection *c, int ok) {
  struct conn_query *q = c->first_query;
  struct connection *d = c->first_query->requester;
  assert (d);
  if (d->generation == c->first_query->req_generation) {
    d->queries_ok += ok;
    MCS_DATA(d)->complete_count++;
  }
  active_queries--;
  c->unreliability >>= 1;
  delete_conn_query (q);
  zfree (q, sizeof (*q));
  return 0;
}