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
struct ssh {int dummy; } ;
struct permission_set {scalar_t__ all_permitted; } ;

/* Variables and functions */
 int FORWARD_LOCAL ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fwd_ident (int,int) ; 
 int /*<<< orphan*/  permission_set_add (struct ssh*,int,int,char*,int,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 struct permission_set* permission_set_get (struct ssh*,int) ; 

void
channel_add_permission(struct ssh *ssh, int who, int where,
    char *host, int port)
{
	int local = where == FORWARD_LOCAL;
	struct permission_set *pset = permission_set_get(ssh, where);

	debug("allow %s forwarding to host %s port %d",
	    fwd_ident(who, where), host, port);
	/*
	 * Remote forwards set listen_host/port, local forwards set
	 * host/port_to_connect.
	 */
	permission_set_add(ssh, who, where,
	    local ? host : 0, local ? port : 0,
	    local ? NULL : host, NULL, local ? 0 : port, NULL);
	pset->all_permitted = 0;
}