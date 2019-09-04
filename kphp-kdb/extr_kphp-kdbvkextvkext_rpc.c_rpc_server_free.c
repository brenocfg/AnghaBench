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
struct rpc_server {scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PFREE (int) ; 
 int /*<<< orphan*/  rpc_server_sleep (struct rpc_server*) ; 
 int /*<<< orphan*/  zzfree (struct rpc_server*,int) ; 

__attribute__((used)) static void rpc_server_free (struct rpc_server *server) /* {{{ */ {
  rpc_server_sleep (server);

  server->magic = 0;
  zzfree (server, sizeof (*server));
  ADD_PFREE (sizeof (*server));
}