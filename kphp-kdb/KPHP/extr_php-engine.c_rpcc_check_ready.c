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
struct connection {int flags; scalar_t__ status; scalar_t__ ready; int fd; double last_query_sent_time; double last_response_time; } ;
struct TYPE_2__ {int in_packet_num; } ;

/* Variables and functions */
 int C_FAILED ; 
 TYPE_1__* RPCC_DATA (struct connection*) ; 
 double RPC_CONNECT_TIMEOUT ; 
 double RPC_FAIL_INTERVAL ; 
 double RPC_STOP_INTERVAL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ conn_connecting ; 
 scalar_t__ conn_error ; 
 scalar_t__ conn_expect_query ; 
 scalar_t__ conn_reading_answer ; 
 scalar_t__ conn_running ; 
 scalar_t__ conn_wait_answer ; 
 scalar_t__ cr_busy ; 
 scalar_t__ cr_failed ; 
 int cr_notyet ; 
 scalar_t__ cr_ok ; 
 scalar_t__ cr_stopped ; 
 int /*<<< orphan*/  fail_connection (struct connection*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__,double,double,double) ; 
 int /*<<< orphan*/  lrand48 () ; 
 int /*<<< orphan*/  net_rpc_send_ping (struct connection*,int /*<<< orphan*/ ) ; 
 double precise_now ; 
 double rpc_ping_interval ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int rpcc_check_ready (struct connection *c) {
  /*assert (c->status != conn_none);*/
  /*if (c->status == conn_none || c->status == conn_connecting || RPCC_DATA(c)->in_packet_num < 0) {*/
    /*return c->ready = cr_notyet;*/
  /*}*/
  /*if (c->status == conn_error || c->ready == cr_failed) {*/
    /*return c->ready = cr_failed;*/
  /*}*/
  /*return c->ready = cr_ok;*/

  if ((c->flags & C_FAILED) || c->status == conn_error) {
    if (verbosity > 1 && c->ready != cr_failed) {
      fprintf (stderr, "changing connection %d readiness from %d to %d [FAILED] lq=%.03f lr=%.03f now=%.03f\n", c->fd, c->ready, cr_failed, c->last_query_sent_time, c->last_response_time, precise_now);
    }
    return c->ready = cr_failed;
  }

  if (RPCC_DATA(c)->in_packet_num < 0) {
    if (RPCC_DATA(c)->in_packet_num == -1 && c->status == conn_running) {
      if (verbosity > 1 && c->ready != cr_ok) {
        fprintf (stderr, "changing connection %d readiness from %d to %d [OK] lq=%.03f lr=%.03f now=%.03f\n", c->fd, c->ready, cr_ok, c->last_query_sent_time, c->last_response_time, precise_now);
      }
      return c->ready = cr_ok;
    }

    assert (c->last_query_sent_time != 0);
    if (c->last_query_sent_time < precise_now - RPC_CONNECT_TIMEOUT) {
      fail_connection (c, -6);
      return c->ready = cr_failed;
    }
    return c->ready = cr_notyet;
  }
  assert (c->status != conn_connecting);

  if (c->last_query_sent_time < precise_now - rpc_ping_interval) {
    net_rpc_send_ping (c, lrand48());
    c->last_query_sent_time = precise_now;
  }

  assert (c->last_response_time != 0);
  if (c->last_response_time < precise_now - RPC_FAIL_INTERVAL) {
    if (verbosity > 1 && c->ready != cr_failed) {
      fprintf (stderr, "changing connection %d readiness from %d to %d [FAILED] lq=%.03f lr=%.03f now=%.03f\n", c->fd, c->ready, cr_failed, c->last_query_sent_time, c->last_response_time, precise_now);
    }
    fail_connection (c, -5);
    return c->ready = cr_failed;
  }

  if (c->last_response_time < precise_now - RPC_STOP_INTERVAL) {
    if (verbosity > 1 && c->ready != cr_stopped) {
      fprintf (stderr, "changing connection %d readiness from %d to %d [STOPPED] lq=%.03f lr=%.03f now=%.03f\n", c->fd, c->ready, cr_stopped, c->last_query_sent_time, c->last_response_time, precise_now);
    }
    return c->ready = cr_stopped;
  }

  if (c->status == conn_wait_answer || c->status == conn_expect_query || c->status == conn_reading_answer) {
    if (verbosity > 1 && c->ready != cr_ok) {
      fprintf (stderr, "changing connection %d readiness from %d to %d [OK] lq=%.03f lr=%.03f now=%.03f\n", c->fd, c->ready, cr_ok, c->last_query_sent_time, c->last_response_time, precise_now);
    }
    return c->ready = cr_ok;
  }

  if (c->status == conn_running) {
    if (verbosity > 1 && c->ready != cr_busy) {
      fprintf (stderr, "changing connection %d readiness from %d to %d [BUSY] lq=%.03f lr=%.03f now=%.03f\n", c->fd, c->ready, cr_busy, c->last_query_sent_time, c->last_response_time, precise_now);
    }
    return c->ready = cr_busy;
  }

  assert (0);
  return c->ready = cr_failed;
}