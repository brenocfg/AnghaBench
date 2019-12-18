#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int user_id; } ;
typedef  TYPE_2__ user_t ;
struct connection {int fd; } ;
struct TYPE_5__ {scalar_t__ wakeup_time; } ;
struct conn_query {scalar_t__ start_time; TYPE_1__ timer; int /*<<< orphan*/ * cq_type; scalar_t__ extra; struct connection* requester; struct connection* outbound; scalar_t__ custom_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ USER_PCONN (TYPE_2__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_utime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  history_cq_func ; 
 int /*<<< orphan*/  insert_conn_query (struct conn_query*) ; 
 int /*<<< orphan*/  pending_http_queries ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 struct conn_query* zmalloc (int) ; 

int create_persistent_history_query (user_t *U, struct connection *c, double timeout) {
  struct conn_query *Q = zmalloc (sizeof (struct conn_query));

  if (verbosity > 1) {
    fprintf (stderr, "create_persistent_history_query(%p[%d], %p[%d]): Q=%p\n", U, U->user_id, c, c->fd, Q);
  }

  Q->custom_type = 0;
  Q->outbound = (struct connection *) USER_PCONN (U);
  Q->requester = c;
  Q->start_time = /*c->query_start_time*/get_utime (CLOCK_MONOTONIC);
  Q->extra = 0;
  Q->cq_type = &history_cq_func;
  Q->timer.wakeup_time = (timeout > 0 ? Q->start_time + timeout : 0);

  pending_http_queries++;
  insert_conn_query (Q);

  if (verbosity > 1) {
    fprintf (stderr, "after insert_conn_query()\n");
  }

  return 1;
}