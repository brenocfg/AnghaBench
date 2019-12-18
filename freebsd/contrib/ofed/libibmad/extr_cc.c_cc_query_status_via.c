#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct ibmad_port {int dummy; } ;
typedef  int /*<<< orphan*/  ib_rpc_t ;
struct TYPE_7__ {unsigned int id; unsigned int mod; } ;
struct TYPE_8__ {unsigned int timeout; int rstatus; int /*<<< orphan*/  cckey; int /*<<< orphan*/  mgtclass; int /*<<< orphan*/  dataoffs; int /*<<< orphan*/  datasz; TYPE_1__ attr; int /*<<< orphan*/  method; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ ib_rpc_cc_t ;
struct TYPE_9__ {int qp; scalar_t__ qkey; } ;
typedef  TYPE_3__ ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int IB_CC_ATTR_CONGESTION_LOG ; 
 int /*<<< orphan*/  IB_CC_CLASS ; 
 int /*<<< orphan*/  IB_CC_DATA_OFFS ; 
 int /*<<< orphan*/  IB_CC_DATA_SZ ; 
 int /*<<< orphan*/  IB_CC_LOG_DATA_OFFS ; 
 int /*<<< orphan*/  IB_CC_LOG_DATA_SZ ; 
 scalar_t__ IB_DEFAULT_QP1_QKEY ; 
 int /*<<< orphan*/  IB_MAD_METHOD_GET ; 
 void* mad_rpc (struct ibmad_port const*,int /*<<< orphan*/ *,TYPE_3__*,void*,void*) ; 
 int /*<<< orphan*/  portid2str (TYPE_3__*) ; 

void *cc_query_status_via(void *rcvbuf, ib_portid_t * portid,
			  unsigned attrid, unsigned mod, unsigned timeout,
			  int *rstatus, const struct ibmad_port * srcport,
			  uint64_t cckey)
{
	ib_rpc_cc_t rpc = { 0 };
	void *res;

	DEBUG("attr 0x%x mod 0x%x route %s", attrid, mod, portid2str(portid));
	rpc.method = IB_MAD_METHOD_GET;
	rpc.attr.id = attrid;
	rpc.attr.mod = mod;
	rpc.timeout = timeout;
	if (attrid == IB_CC_ATTR_CONGESTION_LOG) {
		rpc.datasz = IB_CC_LOG_DATA_SZ;
		rpc.dataoffs = IB_CC_LOG_DATA_OFFS;
	}
	else {
		rpc.datasz = IB_CC_DATA_SZ;
		rpc.dataoffs = IB_CC_DATA_OFFS;
	}
	rpc.mgtclass = IB_CC_CLASS;
	rpc.cckey = cckey;

	portid->qp = 1;
	if (!portid->qkey)
		portid->qkey = IB_DEFAULT_QP1_QKEY;

	res = mad_rpc(srcport, (ib_rpc_t *)&rpc, portid, rcvbuf, rcvbuf);
	if (rstatus)
		*rstatus = rpc.rstatus;

	return res;
}