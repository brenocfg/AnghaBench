#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct connection {int pending_queries; } ;
typedef  int /*<<< orphan*/  queue ;
struct TYPE_6__ {int n; TYPE_1__** k; } ;
typedef  TYPE_2__ qkey_group ;
struct TYPE_7__ {TYPE_1__* extra; } ;
struct TYPE_5__ {int /*<<< orphan*/  subscribed; int /*<<< orphan*/  lock; int /*<<< orphan*/  name; int /*<<< orphan*/  conn; int /*<<< orphan*/ * q; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 TYPE_4__* HTS_DATA (struct connection*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_history_query (int /*<<< orphan*/ *,struct connection*,double,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,double) ; 
 int /*<<< orphan*/  get_utime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int create_history_query_group (qkey_group *g, struct connection *c, double timeout) {
  int i;

  if (verbosity > 2) {
    fprintf (stderr, "create_history_query_group (size = %d) (timeout = %lf)\n", g->n, timeout);
  }
  for (i = 0; i < g->n; i++) {
    queue *q = g->k[i]->q;
    assert (q != NULL);
    HTS_DATA (c)->extra = g->k[i];
    create_history_query (q, c, timeout, &g->k[i]->conn, g->k[i]->name);
    g->k[i]->lock++;
    g->k[i]->subscribed = get_utime (CLOCK_MONOTONIC);
  }
  c->pending_queries = 1;

  return 1;
}