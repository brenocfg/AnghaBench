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
struct connection {int fd; } ;
struct conn_query_functions {int dummy; } ;
struct TYPE_2__ {scalar_t__ wakeup_time; } ;
struct conn_query {scalar_t__ start_time; TYPE_1__ timer; struct conn_query_functions* cq_type; scalar_t__ extra; struct connection* requester; struct connection* outbound; scalar_t__ custom_type; } ;
struct aio_connection {int fd; struct conn_query* first_query; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  active_aio_queries ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_utime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_conn_query (struct conn_query*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tot_aio_queries ; 
 int verbosity ; 
 struct conn_query* zmalloc (int) ; 

int create_aio_query (struct aio_connection *a, struct connection *c, double timeout, struct conn_query_functions *cq) {
  struct conn_query *Q = zmalloc (sizeof (struct conn_query));

  if (verbosity > 1) {
    fprintf (stderr, "create_query(%p[%d], %p[%d]): Q=%p\n", a, a->fd, c, c->fd, Q);
  }

  Q->custom_type = 0;
  Q->outbound = (struct connection *)a;
  Q->requester = c;
  Q->start_time = /*c->query_start_time*/get_utime (CLOCK_MONOTONIC);
  Q->extra = 0;
  Q->cq_type = cq;
  Q->timer.wakeup_time = (timeout > 0 ? Q->start_time + timeout : 0);

  if (verbosity > 1 && a->first_query != (struct conn_query *) a) {
    fprintf (stderr, "!NOTICE! inserting second query to %p\n", a);
  }

  insert_conn_query (Q);
  active_aio_queries++;
  tot_aio_queries++;

  if (verbosity > 1) {
    fprintf (stderr, "after insert_conn_query()\n");
  }

  return 1;
}