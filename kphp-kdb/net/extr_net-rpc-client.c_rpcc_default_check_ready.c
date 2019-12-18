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
struct connection {int flags; scalar_t__ status; int ready; scalar_t__ last_query_sent_time; } ;
struct TYPE_2__ {int in_packet_num; } ;

/* Variables and functions */
 int C_FAILED ; 
 TYPE_1__* RPCC_DATA (struct connection*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ conn_connecting ; 
 scalar_t__ conn_error ; 
 scalar_t__ conn_expect_query ; 
 scalar_t__ conn_reading_answer ; 
 scalar_t__ conn_running ; 
 scalar_t__ conn_wait_answer ; 
 int cr_failed ; 
 int cr_notyet ; 
 int cr_ok ; 
 int /*<<< orphan*/  fail_connection (struct connection*,int) ; 
 double const precise_now ; 

int rpcc_default_check_ready (struct connection *c) {
  if ((c->flags & C_FAILED) || c->status == conn_error) {
    return c->ready = cr_failed;
  }

  const double CONNECT_TIMEOUT = 3.0;
  if (c->status == conn_connecting || RPCC_DATA(c)->in_packet_num < 0) {
    if (RPCC_DATA(c)->in_packet_num == -1 && c->status == conn_running) {
      return c->ready = cr_ok;
    }

    assert (c->last_query_sent_time != 0);
    if (c->last_query_sent_time < precise_now - CONNECT_TIMEOUT) {
      fail_connection (c, -6);
      return c->ready = cr_failed;
    }
    return c->ready = cr_notyet;
  }
    
  if (c->status == conn_wait_answer || c->status == conn_reading_answer || c->status == conn_expect_query) {
    return c->ready = cr_ok;
  }

  return c->ready = cr_failed;
}