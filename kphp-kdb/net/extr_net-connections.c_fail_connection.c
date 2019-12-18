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
struct connection {int flags; scalar_t__ status; int error; int /*<<< orphan*/  ev; TYPE_1__* target; } ;
struct TYPE_2__ {int /*<<< orphan*/  active_outbound_connections; } ;

/* Variables and functions */
 int C_FAILED ; 
 int C_WANTRD ; 
 int C_WANTWR ; 
 int /*<<< orphan*/  active_connections ; 
 int /*<<< orphan*/  active_outbound_connections ; 
 scalar_t__ conn_connecting ; 
 scalar_t__ conn_error ; 
 int /*<<< orphan*/  put_event_into_heap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  total_connect_failures ; 
 int /*<<< orphan*/  total_failed_connections ; 

int fail_connection (struct connection *c, int err) {
  if (!(c->flags & C_FAILED)) {
    total_failed_connections++;
    if (c->status == conn_connecting) {
      total_connect_failures++;
    }
  }
  c->flags |= C_FAILED;
  c->flags &= ~(C_WANTRD | C_WANTWR);
  if (c->status == conn_connecting) {
    c->target->active_outbound_connections++;
    active_outbound_connections++;
    active_connections++;
  }
  c->status = conn_error;
  if (c->error >= 0) {
    c->error = err;
  }
  put_event_into_heap (c->ev);
  return 0;
}