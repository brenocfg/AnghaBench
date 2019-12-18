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
struct rpc_server {char const* error; int errnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_MALLOC (scalar_t__) ; 
 int /*<<< orphan*/  rpc_global_seterror (char const*,int) ; 
 char const* strdup (char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  zzfree (char const*,scalar_t__) ; 

__attribute__((used)) static void rpc_server_seterror (struct rpc_server *server, const char *error, int errnum) { /* {{{ */
  if (error) {
    if (server->error) {
      zzfree (server->error, strlen (server->error) + 1);
    }
    
    server->error = strdup (error);
    server->errnum = errnum;
    ADD_MALLOC (strlen (error) + 1);

    rpc_global_seterror (error, errnum);
  }
}