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
struct ibmad_port {int /*<<< orphan*/ * class_agents; int /*<<< orphan*/  port_id; } ;
struct TYPE_4__ {int dataoffs; int mgtclass; int /*<<< orphan*/  timeout; int /*<<< orphan*/  datasz; } ;
typedef  TYPE_1__ ib_rpc_t ;
typedef  int /*<<< orphan*/  ib_rmpp_hdr_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  IBWARN (char*,int,...) ; 
 scalar_t__ IB_MAD_SIZE ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ibdebug ; 
 scalar_t__ mad_build_pkt (void*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  mad_get_timeout (struct ibmad_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ umad_get_mad (void*) ; 
 scalar_t__ umad_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ umad_size () ; 
 int /*<<< orphan*/  xdump (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

int mad_send_via(ib_rpc_t * rpc, ib_portid_t * dport, ib_rmpp_hdr_t * rmpp,
		 void *data, struct ibmad_port *srcport)
{
	uint8_t pktbuf[1024];
	void *umad = pktbuf;

	memset(pktbuf, 0, umad_size() + IB_MAD_SIZE);

	DEBUG("rmpp %p data %p", rmpp, data);

	if (mad_build_pkt(umad, rpc, dport, rmpp, data) < 0)
		return -1;

	if (ibdebug) {
		IBWARN("data offs %d sz %d", rpc->dataoffs, rpc->datasz);
		xdump(stderr, "mad send data\n",
		      (char *)umad_get_mad(umad) + rpc->dataoffs, rpc->datasz);
	}

	if (umad_send(srcport->port_id, srcport->class_agents[rpc->mgtclass & 0xff],
		      umad, IB_MAD_SIZE, mad_get_timeout(srcport, rpc->timeout),
		      0) < 0) {
		IBWARN("send failed; %s", strerror(errno));
		return -1;
	}

	return 0;
}