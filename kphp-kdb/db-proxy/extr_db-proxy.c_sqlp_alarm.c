#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int total_bytes; int unprocessed_bytes; } ;
struct TYPE_3__ {int total_bytes; int unprocessed_bytes; } ;
struct connection {int fd; int pending_queries; int status; int flags; TYPE_2__ Out; TYPE_1__ In; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ conn_wait_net ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int sqlp_wakeup (struct connection*) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int sqlp_alarm (struct connection *c) {
  if (verbosity > 1) {
    fprintf (stderr, "proxy_mysql_server connection %d timeout alarm, %d queries pending, status=%d\n", c->fd, c->pending_queries, c->status);
  }
  if (c->status != conn_wait_net) {
    fprintf (stderr, "connection %d (IN: %d+%d, OUT: %d+%d, FLAGS: %d) is in state %d, conn_wait_net expected!\n", c->fd, c->In.total_bytes, c->In.unprocessed_bytes, c->Out.total_bytes, c->Out.unprocessed_bytes, c->flags, c->status);
  }
  assert (c->status == conn_wait_net);
//  send_error_packet (c, 1045, 28000, "Failed", 6, ++SQLS_DATA(c)->output_packet_seq);
  return sqlp_wakeup (c);
  /*c->status = conn_error;
  if (verbosity > 0) {
    fprintf (stderr, "sql server connection timeout for connection %d --> switching to error status\n", c->fd);
  }*/
  //return /*-1*/0;
}