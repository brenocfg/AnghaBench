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
struct rpc_server {scalar_t__ status; scalar_t__ sfd; double timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  lrand48 () ; 
 double precise_now ; 
 scalar_t__ rpc_ping_send (struct rpc_server*,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_server_disconnect (struct rpc_server*) ; 
 scalar_t__ rpc_status_connected ; 
 scalar_t__ rpc_work (struct rpc_server*,int,double) ; 
 int /*<<< orphan*/  update_precise_now () ; 

__attribute__((used)) static int rpc_ping (struct rpc_server *server) { /* {{{ */
//  double timeout = 0.1;
  if (server->status != rpc_status_connected || server->sfd < 0) {
    return -1;
  }
  update_precise_now ();
  double t = precise_now + server->timeout;
  if (rpc_ping_send (server, t, lrand48 ()) < 0) {
    rpc_server_disconnect (server);
    return -1;
  }
  if (rpc_work (server, 1, t) < 0) {
    rpc_server_disconnect (server);
    return -1;
  }
  return 1;
}