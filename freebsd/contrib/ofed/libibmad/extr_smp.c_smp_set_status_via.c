#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ibmad_port {int /*<<< orphan*/  smp_mkey; } ;
struct TYPE_10__ {unsigned int id; unsigned int mod; } ;
struct TYPE_11__ {unsigned int timeout; int rstatus; int /*<<< orphan*/  mkey; int /*<<< orphan*/  dataoffs; int /*<<< orphan*/  datasz; TYPE_2__ attr; int /*<<< orphan*/  method; int /*<<< orphan*/  mgtclass; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ ib_rpc_t ;
struct TYPE_9__ {int drslid; int drdlid; } ;
struct TYPE_12__ {scalar_t__ lid; scalar_t__ qp; scalar_t__ sl; TYPE_1__ drpath; } ;
typedef  TYPE_4__ ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IB_MAD_METHOD_SET ; 
 int /*<<< orphan*/  IB_SMI_CLASS ; 
 int /*<<< orphan*/  IB_SMI_DIRECT_CLASS ; 
 int /*<<< orphan*/  IB_SMP_DATA_OFFS ; 
 int /*<<< orphan*/  IB_SMP_DATA_SIZE ; 
 int /*<<< orphan*/ * mad_rpc (struct ibmad_port const*,TYPE_3__*,TYPE_4__*,void*,void*) ; 
 int /*<<< orphan*/  portid2str (TYPE_4__*) ; 

uint8_t *smp_set_status_via(void *data, ib_portid_t * portid, unsigned attrid,
			    unsigned mod, unsigned timeout, int *rstatus,
			    const struct ibmad_port *srcport)
{
	ib_rpc_t rpc = { 0 };
	uint8_t *res;

	DEBUG("attr 0x%x mod 0x%x route %s", attrid, mod, portid2str(portid));
	if ((portid->lid <= 0) ||
	    (portid->drpath.drslid == 0xffff) ||
	    (portid->drpath.drdlid == 0xffff))
		rpc.mgtclass = IB_SMI_DIRECT_CLASS;	/* direct SMI */
	else
		rpc.mgtclass = IB_SMI_CLASS;	/* Lid routed SMI */

	rpc.method = IB_MAD_METHOD_SET;
	rpc.attr.id = attrid;
	rpc.attr.mod = mod;
	rpc.timeout = timeout;
	rpc.datasz = IB_SMP_DATA_SIZE;
	rpc.dataoffs = IB_SMP_DATA_OFFS;
	rpc.mkey = srcport->smp_mkey;

	portid->sl = 0;
	portid->qp = 0;

	res = mad_rpc(srcport, &rpc, portid, data, data);
	if (rstatus)
		*rstatus = rpc.rstatus;
	return res;
}