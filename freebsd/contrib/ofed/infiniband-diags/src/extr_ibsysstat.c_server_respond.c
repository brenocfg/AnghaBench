#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  rport ;
struct TYPE_12__ {void* mod; void* id; } ;
struct TYPE_13__ {int method; int /*<<< orphan*/  timeout; void* mgtclass; TYPE_1__ attr; int /*<<< orphan*/  trid; void* oui; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ ib_rpc_t ;
struct TYPE_14__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ ib_rmpp_hdr_t ;
struct TYPE_15__ {int qp; void* qkey; int /*<<< orphan*/  gid; scalar_t__ grh_present; int /*<<< orphan*/  sl; int /*<<< orphan*/  lid; } ;
typedef  TYPE_4__ ib_portid_t ;
struct TYPE_16__ {int /*<<< orphan*/  gid; scalar_t__ grh_present; int /*<<< orphan*/  sl; int /*<<< orphan*/  qkey; int /*<<< orphan*/  qpn; int /*<<< orphan*/  lid; } ;
typedef  TYPE_5__ ib_mad_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,...) ; 
 void* IB_DEFAULT_QP1_QKEY ; 
 int /*<<< orphan*/  IB_MAD_ATTRID_F ; 
 int /*<<< orphan*/  IB_MAD_ATTRMOD_F ; 
 int IB_MAD_METHOD_GET ; 
 int /*<<< orphan*/  IB_MAD_MGMTCLASS_F ; 
 int IB_MAD_RESPONSE ; 
 int IB_MAD_SIZE ; 
 int /*<<< orphan*/  IB_MAD_TRID_F ; 
 int /*<<< orphan*/  IB_RMPP_FLAG_ACTIVE ; 
 int /*<<< orphan*/  IB_VEND2_OUI_F ; 
 int ibdebug ; 
 scalar_t__ mad_build_pkt (void*,TYPE_2__*,TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* mad_get_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mad_get_field64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mad_rpc_class_agent (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mad_rpc_portid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portid2str (TYPE_4__*) ; 
 int /*<<< orphan*/  srcport ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * umad_get_mad (void*) ; 
 TYPE_5__* umad_get_mad_addr (void*) ; 
 scalar_t__ umad_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int server_respond(void *umad, int size)
{
	ib_rpc_t rpc = { 0 };
	ib_rmpp_hdr_t rmpp = { 0 };
	ib_portid_t rport;
	uint8_t *mad = umad_get_mad(umad);
	ib_mad_addr_t *mad_addr;

	if (!(mad_addr = umad_get_mad_addr(umad)))
		return -1;

	memset(&rport, 0, sizeof(rport));

	rport.lid = ntohs(mad_addr->lid);
	rport.qp = ntohl(mad_addr->qpn);
	rport.qkey = ntohl(mad_addr->qkey);
	rport.sl = mad_addr->sl;
	if (!rport.qkey && rport.qp == 1)
		rport.qkey = IB_DEFAULT_QP1_QKEY;
	rport.grh_present = mad_addr->grh_present;
	if (rport.grh_present)
		memcpy(rport.gid, mad_addr->gid, 16);

	rpc.mgtclass = mad_get_field(mad, 0, IB_MAD_MGMTCLASS_F);
	rpc.method = IB_MAD_METHOD_GET | IB_MAD_RESPONSE;
	rpc.attr.id = mad_get_field(mad, 0, IB_MAD_ATTRID_F);
	rpc.attr.mod = mad_get_field(mad, 0, IB_MAD_ATTRMOD_F);
	rpc.oui = mad_get_field(mad, 0, IB_VEND2_OUI_F);
	rpc.trid = mad_get_field64(mad, 0, IB_MAD_TRID_F);

	if (size > IB_MAD_SIZE)
		rmpp.flags = IB_RMPP_FLAG_ACTIVE;

	DEBUG("responding %d bytes to %s, attr 0x%x mod 0x%x qkey %x",
	      size, portid2str(&rport), rpc.attr.id, rpc.attr.mod, rport.qkey);

	if (mad_build_pkt(umad, &rpc, &rport, &rmpp, 0) < 0)
		return -1;

	if (ibdebug > 1)
		xdump(stderr, "mad respond pkt\n", mad, IB_MAD_SIZE);

	if (umad_send(mad_rpc_portid(srcport),
		      mad_rpc_class_agent(srcport, rpc.mgtclass), umad, size,
		      rpc.timeout, 0) < 0) {
		DEBUG("send failed; %m");
		return -1;
	}

	return 0;
}