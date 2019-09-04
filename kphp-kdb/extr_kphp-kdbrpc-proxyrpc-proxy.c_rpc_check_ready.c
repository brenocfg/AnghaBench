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
struct connection {scalar_t__ status; double last_response_time; double last_query_sent_time; int unreliability; int ready; int fd; double last_query_timeout; int flags; } ;
struct TYPE_2__ {scalar_t__ in_packet_num; } ;

/* Variables and functions */
 double CONNECT_TIMEOUT ; 
 int C_FAILED ; 
 double FAIL_INTERVAL ; 
 double PING_INTERVAL ; 
 TYPE_1__* RPCS_DATA (struct connection*) ; 
 double STOP_INTERVAL ; 
 scalar_t__ conn_connecting ; 
 scalar_t__ conn_reading_answer ; 
 scalar_t__ conn_wait_answer ; 
 int cr_failed ; 
 int cr_notyet ; 
 scalar_t__ cr_ok ; 
 scalar_t__ cr_stopped ; 
 int /*<<< orphan*/  fail_connection (struct connection*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,scalar_t__,double,double,double,double,double,int) ; 
 int /*<<< orphan*/  lrand48 () ; 
 int /*<<< orphan*/  net_rpc_send_ping (struct connection*,int /*<<< orphan*/ ) ; 
 double precise_now ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int rpc_check_ready (struct connection *c) {
  double first_query_time = 0;
  double adj_precise_now = precise_now;

  if (c->status == conn_connecting || (c->last_response_time == 0 && (c->status == conn_wait_answer || c->status == conn_reading_answer)) ||  RPCS_DATA(c)->in_packet_num < 0) {
    if (c->last_query_sent_time < adj_precise_now - CONNECT_TIMEOUT) {
      fail_connection (c, -6);
      return cr_failed;
    }
    return cr_notyet;
  }
  if (c->last_query_sent_time < adj_precise_now - PING_INTERVAL) {
    net_rpc_send_ping (c, lrand48 ());
    c->last_query_sent_time = precise_now;
  }

  if (c->last_response_time < adj_precise_now - FAIL_INTERVAL || c->unreliability > 5000) {
    if (verbosity > 1 && c->ready != cr_failed) {
      fprintf (stderr, "changing connection %d readiness from %d to %d [FAILED] fq=%.03f lq=%.03f lqt=%.03f lr=%.03f now=%.03f unr=%d\n", c->fd, c->ready, cr_failed, first_query_time, c->last_query_sent_time, c->last_query_timeout, c->last_response_time, precise_now, c->unreliability);
    }
    fail_connection (c, -5);
    return c->ready = cr_failed;
  }

  if (c->last_response_time < adj_precise_now - STOP_INTERVAL || c->unreliability > 2000) {
    if (verbosity > 1 && c->ready != cr_stopped) {
      fprintf (stderr, "changing connection %d readiness from %d to %d [STOPPED] fq=%.03f lq=%.03f lqt=%.03f lr=%.03f now=%.03f unr=%d\n", c->fd, c->ready, cr_stopped, first_query_time, c->last_query_sent_time, c->last_query_timeout, c->last_response_time, precise_now, c->unreliability);
    }
    return c->ready = cr_stopped;
  }
    
  if (!(c->flags & C_FAILED) && c->last_response_time > 0 && (c->status == conn_wait_answer || c->status == conn_reading_answer)) {
    if (verbosity > 1 && c->ready != cr_ok) {
      fprintf (stderr, "changing connection %d readiness from %d to %d [OK] fq=%.03f lq=%.03f lqt=%.03f lr=%.03f now=%.03f unr=%d\n", c->fd, c->ready, cr_ok, first_query_time, c->last_query_sent_time, c->last_query_timeout, c->last_response_time, precise_now, c->unreliability);
    }
    return c->ready = cr_ok;
  }

  return c->ready = cr_failed;
}