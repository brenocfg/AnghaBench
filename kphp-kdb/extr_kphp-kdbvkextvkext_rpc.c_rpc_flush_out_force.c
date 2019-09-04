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
struct rpc_server {int dummy; } ;

/* Variables and functions */
 scalar_t__ rpc_flush_out (struct rpc_server*,double) ; 
 int /*<<< orphan*/  rpc_server_failure (struct rpc_server*) ; 
 int /*<<< orphan*/  rpc_server_seterror (struct rpc_server*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpc_flush_out_force (struct rpc_server *server, double timeout) {
  if (rpc_flush_out (server, timeout) > 0) {
    rpc_server_seterror (server, "Flush timeout", 0);
    rpc_server_failure (server);
    return -1;
  }
  return 0;
}