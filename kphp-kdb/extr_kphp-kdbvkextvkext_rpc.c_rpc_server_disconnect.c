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
struct rpc_server {int sfd; scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  active_net_connections ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  net_connections_fails ; 
 scalar_t__ rpc_status_connected ; 
 scalar_t__ rpc_status_disconnected ; 

__attribute__((used)) static void rpc_server_disconnect (struct rpc_server *server) { /* {{{ */
  if (server->sfd >= 0) {
    close (server->sfd);
    server->sfd = -1;
    if (server->status == rpc_status_connected) {
      active_net_connections --;
    }
    net_connections_fails ++;
  }
  server->status = rpc_status_disconnected;
}