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
struct rpc_server {int out_bytes; } ;

/* Variables and functions */
 scalar_t__ rpc_sock_write (struct rpc_server*,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rpc_flush_out (struct rpc_server *server, double timeout) {
  if (server->out_bytes) {
    if (rpc_sock_write (server, timeout, 0, 0, server->out_bytes) < 0) { 
      return -1;
    }
  }
  return server->out_bytes;
}