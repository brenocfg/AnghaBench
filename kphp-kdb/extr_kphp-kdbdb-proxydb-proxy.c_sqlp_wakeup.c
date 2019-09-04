#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int total_bytes; int unprocessed_bytes; } ;
struct TYPE_4__ {int total_bytes; int unprocessed_bytes; } ;
struct connection {int fd; int queries_ok; scalar_t__ status; int flags; scalar_t__ pending_queries; scalar_t__ generation; TYPE_2__ Out; TYPE_1__ In; } ;
struct TYPE_6__ {int query_state; int /*<<< orphan*/  output_packet_seq; } ;

/* Variables and functions */
 int C_REPARSE ; 
 int C_WANTWR ; 
 TYPE_3__* SQLS_DATA (struct connection*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_connection_timeout (struct connection*) ; 
 scalar_t__ conn_error ; 
 scalar_t__ conn_expect_query ; 
 scalar_t__ conn_generation ; 
 scalar_t__ conn_wait_net ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int query_failed ; 
 void* query_none ; 
#define  query_running 129 
#define  query_wait_target 128 
 int /*<<< orphan*/  send_error_packet (struct connection*,int,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int sqlp_wakeup (struct connection *c) {
  if (verbosity > 1) {
    fprintf (stderr, "connection %d wakes up, query_state=%d, queries_ok=%d\n", c->fd, SQLS_DATA(c)->query_state, c->queries_ok);
  }

  if (!c->queries_ok) {
    if (c->status != conn_wait_net) {
      fprintf (stderr, "connection %d (IN: %d+%d, OUT: %d+%d, FLAGS: %d) is in state %d, conn_wait_net expected!\n", c->fd, c->In.total_bytes, c->In.unprocessed_bytes, c->Out.total_bytes, c->Out.unprocessed_bytes, c->flags, c->status);
    }
    assert (c->status == conn_wait_net);
    switch (SQLS_DATA(c)->query_state) {
    case query_wait_target:
      if (verbosity > 1) {
        fprintf (stderr, "connection %d: switching query_state to query_failed\n", c->fd);
      }
      SQLS_DATA(c)->query_state = query_failed;
      break;
    case query_running:
      if (verbosity > 0) {
        fprintf (stderr, "connection %d: sending Failed packet because of timeout\n", c->fd);
      }
      send_error_packet (c, 1045, 28000, "Failed", 6, ++SQLS_DATA(c)->output_packet_seq);
      SQLS_DATA(c)->query_state = query_none;
      //      c->status = conn_error;
      //      c->error = -7;
      break;
    default:
      fprintf (stderr, "connection %d awakened in impossible query_state\n", c->fd);
      assert (SQLS_DATA(c)->query_state == query_wait_target || SQLS_DATA(c)->query_state == query_running);
    }
  } else if (SQLS_DATA(c)->query_state == query_wait_target) {
    if (verbosity > 1) {
      fprintf (stderr, "connection %d: have ready target, switching query_state from query_wait_target to query_none\n", c->fd);
    }
    SQLS_DATA(c)->query_state = query_none;
  }

  assert (c->queries_ok >= 0);
  c->queries_ok = -1000;

  c->flags |= C_REPARSE;

  if (c->Out.total_bytes + c->Out.unprocessed_bytes > 0) {
    c->flags |= C_WANTWR;
  }

  c->generation = ++conn_generation;
  c->pending_queries = 0;
  //c->target->first_query = c->target->last_query = (struct conn_query *)c->target;
  if (c->status != conn_error) {
    c->status = conn_expect_query;
  }

  clear_connection_timeout (c);
  return 0;
}