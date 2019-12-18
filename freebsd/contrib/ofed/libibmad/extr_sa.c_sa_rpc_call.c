#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ibmad_port {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  recsz; int /*<<< orphan*/  trid; int /*<<< orphan*/  mask; int /*<<< orphan*/  mod; int /*<<< orphan*/  attrid; int /*<<< orphan*/  method; } ;
typedef  TYPE_2__ ib_sa_call_t ;
struct TYPE_10__ {int /*<<< orphan*/  mod; int /*<<< orphan*/  id; } ;
struct TYPE_12__ {unsigned int timeout; int /*<<< orphan*/  recsz; int /*<<< orphan*/  trid; int /*<<< orphan*/  dataoffs; int /*<<< orphan*/  datasz; int /*<<< orphan*/  mask; TYPE_1__ attr; int /*<<< orphan*/  method; int /*<<< orphan*/  mgtclass; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ ib_rpc_t ;
struct TYPE_13__ {scalar_t__ lid; int qp; scalar_t__ qkey; } ;
typedef  TYPE_4__ ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBWARN (char*) ; 
 scalar_t__ IB_DEFAULT_QP1_QKEY ; 
 int /*<<< orphan*/  IB_SA_CLASS ; 
 int /*<<< orphan*/  IB_SA_DATA_OFFS ; 
 int /*<<< orphan*/  IB_SA_DATA_SIZE ; 
 int /*<<< orphan*/ * mad_rpc_rmpp (struct ibmad_port const*,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  portid2str (TYPE_4__*) ; 

uint8_t *sa_rpc_call(const struct ibmad_port *ibmad_port, void *rcvbuf,
		     ib_portid_t * portid, ib_sa_call_t * sa, unsigned timeout)
{
	ib_rpc_t rpc = { 0 };
	uint8_t *p;

	DEBUG("attr 0x%x mod 0x%x route %s", sa->attrid, sa->mod,
	      portid2str(portid));

	if (portid->lid <= 0) {
		IBWARN("only lid routes are supported");
		return NULL;
	}

	rpc.mgtclass = IB_SA_CLASS;
	rpc.method = sa->method;
	rpc.attr.id = sa->attrid;
	rpc.attr.mod = sa->mod;
	rpc.mask = sa->mask;
	rpc.timeout = timeout;
	rpc.datasz = IB_SA_DATA_SIZE;
	rpc.dataoffs = IB_SA_DATA_OFFS;
	rpc.trid = sa->trid;

	portid->qp = 1;
	if (!portid->qkey)
		portid->qkey = IB_DEFAULT_QP1_QKEY;

	p = mad_rpc_rmpp(ibmad_port, &rpc, portid, 0 /*&sa->rmpp */ , rcvbuf);	/* TODO: RMPP */

	sa->recsz = rpc.recsz;

	return p;
}