#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ibmad_port {int /*<<< orphan*/ * class_agents; int /*<<< orphan*/  port_id; } ;
struct TYPE_5__ {int error; } ;
typedef  TYPE_1__ ib_rpc_v1_t ;
struct TYPE_6__ {int mgtclass; int rstatus; int dataoffs; int /*<<< orphan*/  datasz; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_2__ ib_rpc_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ERRS (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBWARN (char*,int,...) ; 
 int /*<<< orphan*/  IB_DRSMP_STATUS_F ; 
 int IB_MAD_RPC_VERSION1 ; 
 int IB_MAD_RPC_VERSION_MASK ; 
 scalar_t__ IB_MAD_SIZE ; 
 int IB_MAD_STS_REDIRECT ; 
 int _do_madrpc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ibdebug ; 
 int mad_build_pkt (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int mad_get_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mad_get_retries (struct ibmad_port const*) ; 
 int /*<<< orphan*/  mad_get_timeout (struct ibmad_port const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  portid2str (int /*<<< orphan*/ *) ; 
 scalar_t__ redirect_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * umad_get_mad (int /*<<< orphan*/ *) ; 
 scalar_t__ umad_size () ; 
 int /*<<< orphan*/  xdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *mad_rpc(const struct ibmad_port *port, ib_rpc_t * rpc,
	      ib_portid_t * dport, void *payload, void *rcvdata)
{
	int status, len;
	uint8_t sndbuf[1024], rcvbuf[1024], *mad;
	ib_rpc_v1_t *rpcv1 = (ib_rpc_v1_t *)rpc;
	int error = 0;

	if ((rpc->mgtclass & IB_MAD_RPC_VERSION_MASK) == IB_MAD_RPC_VERSION1)
		rpcv1->error = 0;
	do {
		len = 0;
		memset(sndbuf, 0, umad_size() + IB_MAD_SIZE);

		if ((len = mad_build_pkt(sndbuf, rpc, dport, 0, payload)) < 0)
			return NULL;

		if ((len = _do_madrpc(port->port_id, sndbuf, rcvbuf,
				      port->class_agents[rpc->mgtclass & 0xff],
				      len, mad_get_timeout(port, rpc->timeout),
				      mad_get_retries(port), &error)) < 0) {
			if ((rpc->mgtclass & IB_MAD_RPC_VERSION_MASK) ==
			    IB_MAD_RPC_VERSION1)
				rpcv1->error = error;
			IBWARN("_do_madrpc failed; dport (%s)",
			       portid2str(dport));
			return NULL;
		}

		mad = umad_get_mad(rcvbuf);
		status = mad_get_field(mad, 0, IB_DRSMP_STATUS_F);

		/* check for exact match instead of only the redirect bit;
		 * that way, weird statuses cause an error, too */
		if (status == IB_MAD_STS_REDIRECT) {
			/* update dport for next request and retry */
			/* bail if redirection fails */
			if (redirect_port(dport, mad))
				break;
		} else
			break;
	} while (1);

	if ((rpc->mgtclass & IB_MAD_RPC_VERSION_MASK) == IB_MAD_RPC_VERSION1)
		rpcv1->error = error;
	rpc->rstatus = status;

	if (status != 0) {
		ERRS("MAD completed with error status 0x%x; dport (%s)",
		     status, portid2str(dport));
		errno = EIO;
		return NULL;
	}

	if (ibdebug) {
		IBWARN("data offs %d sz %d", rpc->dataoffs, rpc->datasz);
		xdump(stderr, "mad data\n", mad + rpc->dataoffs, rpc->datasz);
	}

	if (rcvdata)
		memcpy(rcvdata, mad + rpc->dataoffs, rpc->datasz);

	return rcvdata;
}