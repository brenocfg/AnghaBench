#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dumperinfo {scalar_t__ dumpoff; } ;
struct debugnet_pcb {int dummy; } ;
struct debugnet_conn_params {scalar_t__ dc_server; scalar_t__* dc_herald_data; scalar_t__ dc_herald_datalen; int /*<<< orphan*/  dc_client_port; int /*<<< orphan*/  dc_herald_port; int /*<<< orphan*/  dc_gateway; int /*<<< orphan*/  dc_client; int /*<<< orphan*/  dc_ifp; } ;
typedef  int /*<<< orphan*/  dcp ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {struct debugnet_pcb* nd_pcb; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_6__ {scalar_t__ s_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INADDR_ANY ; 
 int INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  NETDUMP_ACKPORT ; 
 int /*<<< orphan*/  NETDUMP_PORT ; 
 int debugnet_connect (struct debugnet_conn_params*,struct debugnet_pcb**) ; 
 int /*<<< orphan*/  debugnet_get_gw_mac (struct debugnet_pcb*) ; 
 char* inet_ntoa_r (TYPE_1__,char*) ; 
 int /*<<< orphan*/  memset (struct debugnet_conn_params*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ nd_client ; 
 TYPE_3__ nd_conf ; 
 TYPE_2__ nd_gateway ; 
 int /*<<< orphan*/  nd_ifp ; 
 scalar_t__* nd_path ; 
 TYPE_1__ nd_server ; 
 int /*<<< orphan*/  netdump_enabled () ; 
 int /*<<< orphan*/ * panicstr ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strlen (scalar_t__*) ; 

__attribute__((used)) static int
netdump_start(struct dumperinfo *di)
{
	struct debugnet_conn_params dcp;
	struct debugnet_pcb *pcb;
	char buf[INET_ADDRSTRLEN];
	int error;

	error = 0;

	/* Check if the dumping is allowed to continue. */
	if (!netdump_enabled())
		return (EINVAL);

	if (panicstr == NULL) {
		printf(
		    "netdump_start: netdump may only be used after a panic\n");
		return (EINVAL);
	}

	memset(&dcp, 0, sizeof(dcp));

	if (nd_server.s_addr == INADDR_ANY) {
		printf("netdump_start: can't netdump; no server IP given\n");
		return (EINVAL);
	}

	/* We start dumping at offset 0. */
	di->dumpoff = 0;

	dcp.dc_ifp = nd_ifp;

	dcp.dc_client = nd_client.s_addr;
	dcp.dc_server = nd_server.s_addr;
	dcp.dc_gateway = nd_gateway.s_addr;

	dcp.dc_herald_port = NETDUMP_PORT;
	dcp.dc_client_port = NETDUMP_ACKPORT;

	dcp.dc_herald_data = nd_path;
	dcp.dc_herald_datalen = (nd_path[0] == 0) ? 0 : strlen(nd_path) + 1;

	error = debugnet_connect(&dcp, &pcb);
	if (error != 0) {
		printf("failed to contact netdump server\n");
		/* Squash debugnet to something the dumper code understands. */
		return (EINVAL);
	}

	printf("netdumping to %s (%6D)\n", inet_ntoa_r(nd_server, buf),
	    debugnet_get_gw_mac(pcb), ":");
	nd_conf.nd_pcb = pcb;
	return (0);
}