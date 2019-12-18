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

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ NgMkSockNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csock ; 
 int /*<<< orphan*/ * csock_fd ; 
 int /*<<< orphan*/  csock_input ; 
 int /*<<< orphan*/  dsock ; 
 int /*<<< orphan*/ * dsock_fd ; 
 int /*<<< orphan*/  dsock_input ; 
 int /*<<< orphan*/  exit (int) ; 
 void* fd_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module ; 
 scalar_t__ ng_node_id (char*) ; 
 int /*<<< orphan*/  oid_begemotNg ; 
 int /*<<< orphan*/  or_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_index ; 
 scalar_t__ snmp_node ; 
 int /*<<< orphan*/  snmp_nodename ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ng_start(void)
{
	if (snmp_node == 0) {
		if (NgMkSockNode(snmp_nodename, &csock, &dsock) < 0) {
			syslog(LOG_ERR, "NgMkSockNode: %m");
			exit(1);
		}
		snmp_node = ng_node_id(".:");
	}

	if ((csock_fd = fd_select(csock, csock_input, NULL, module)) == NULL) {
		syslog(LOG_ERR, "fd_select failed on csock: %m");
		return;
	}
	if ((dsock_fd = fd_select(dsock, dsock_input, NULL, module)) == NULL) {
		syslog(LOG_ERR, "fd_select failed on dsock: %m");
		return;
	}

	reg_index = or_register(&oid_begemotNg,
	    "The MIB for the NetGraph access module for SNMP.", module);
}