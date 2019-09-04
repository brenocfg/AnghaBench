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
struct rpc_server {int /*<<< orphan*/ * error; } ;

/* Variables and functions */
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zzfree (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void rpc_server_sleep (struct rpc_server *server) { /* {{{ */
  if (server->error != NULL) {
    zzfree (server->error, strlen (server->error) + 1);
    server->error = NULL;
  }
}