#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int qp; scalar_t__ qkey; } ;
typedef  TYPE_1__ ib_portid_t ;

/* Variables and functions */
 scalar_t__ IB_DEFAULT_QP1_QKEY ; 
 int /*<<< orphan*/  IB_SA_CLASS ; 
 int IB_SMI_CLASS ; 
 int IB_SMI_DIRECT_CLASS ; 
 int /*<<< orphan*/  TMO ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mad_rpc_open_port (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int mad_rpc_portid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rereg_and_test_port (char*,int,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_sm_portid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  srcport ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umad_close_port (int) ; 
 int /*<<< orphan*/  umad_done () ; 
 int /*<<< orphan*/ * umad_get_mad (int /*<<< orphan*/ *) ; 
 int umad_register (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int umad_size () ; 
 int /*<<< orphan*/  umad_unregister (int,int) ; 

int main(int argc, char **argv)
{
	char *guid_file = "port_guids.list";
	int mgmt_classes[2] = { IB_SMI_CLASS, IB_SMI_DIRECT_CLASS };
	ib_portid_t dport_id;
	int port, agent;
	uint8_t *umad, *mad;
	int len;

	if (argc > 1)
		guid_file = argv[1];

	srcport = mad_rpc_open_port(NULL, 0, mgmt_classes, 2);
	if (!srcport)
		err("Failed to open port");

	resolve_sm_portid(NULL, 0, &dport_id);
	dport_id.qp = 1;
	if (!dport_id.qkey)
		dport_id.qkey = IB_DEFAULT_QP1_QKEY;

	len = umad_size() + 256;
	umad = calloc(1, len);
	if (!umad) {
		err("cannot alloc mem for umad: %s\n", strerror(errno));
		return -1;
	}
	port = mad_rpc_portid(srcport);

	agent = umad_register(port, IB_SA_CLASS, 2, 0, NULL);

	rereg_and_test_port(guid_file, port, agent, &dport_id, TMO);
	mad = umad_get_mad(umad);

	free(umad);
	umad_unregister(port, agent);
	umad_close_port(port);
	umad_done();

	return 0;
}