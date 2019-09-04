#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct connection {double last_query_timeout; scalar_t__ status; double last_response_time; double last_query_sent_time; int ready; double last_query_time; int unreliability; int fd; int flags; struct conn_query* first_query; int /*<<< orphan*/  Out; } ;
struct conn_query {double start_time; } ;

/* Variables and functions */
 double CONNECT_TIMEOUT ; 
 int C_FAILED ; 
 double RESPONSE_FAIL_TIMEOUT ; 
 scalar_t__ conn_connecting ; 
 scalar_t__ conn_reading_answer ; 
 scalar_t__ conn_wait_answer ; 
 scalar_t__ cr_failed ; 
 int cr_notyet ; 
 scalar_t__ cr_ok ; 
 scalar_t__ cr_stopped ; 
 double drand48 () ; 
 int /*<<< orphan*/  fail_connection (struct connection*,int) ; 
 int /*<<< orphan*/  flush_output (struct connection*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__,double,double,double,double,double,int) ; 
 double ping_interval ; 
 double precise_now ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int mcp_check_ready (struct connection *c) {
  double first_query_time = 0;
  double adj_precise_now = precise_now - c->last_query_timeout;

  if (c->status == conn_connecting || (c->last_response_time == 0 && (c->status == conn_wait_answer || c->status == conn_reading_answer))) {
    if (c->last_query_sent_time < adj_precise_now - CONNECT_TIMEOUT) {
      fail_connection (c, -6);
      return c->ready = cr_failed;
    }
    return c->ready = cr_notyet;
  }

  if (c->last_query_sent_time < adj_precise_now - ping_interval - c->last_query_time && c->first_query == (struct conn_query *) c) {
    write_out (&c->Out, "version\r\n", 9);
    c->last_query_sent_time = precise_now;
    c->last_query_time = drand48() * 0.1;
    flush_output (c);
  }
  if (c->first_query != (struct conn_query *) c) {
    first_query_time = c->first_query->start_time;
  }
  if (c->last_response_time < adj_precise_now - ping_interval*2 || (first_query_time > 0 && first_query_time < adj_precise_now - RESPONSE_FAIL_TIMEOUT) || c->unreliability > 5000) {
    if (verbosity > 1 && c->ready != cr_failed) {
      fprintf (stderr, "changing connection %d readiness from %d to %d [FAILED] fq=%.03f lq=%.03f lqt=%.03f lr=%.03f now=%.03f unr=%d\n", c->fd, c->ready, cr_failed, first_query_time, c->last_query_sent_time, c->last_query_timeout, c->last_response_time, precise_now, c->unreliability);
    }
    fail_connection (c, -5);
    return c->ready = cr_failed;
  }
  if (c->last_response_time < adj_precise_now - ping_interval - 3 || (first_query_time > 0 && first_query_time < adj_precise_now - 3) || c->unreliability > 2000) {
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