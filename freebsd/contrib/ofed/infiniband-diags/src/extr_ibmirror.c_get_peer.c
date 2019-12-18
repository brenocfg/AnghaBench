#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  peerportid ;
struct TYPE_8__ {int cnt; int* p; int drdlid; scalar_t__ drslid; } ;
struct TYPE_9__ {TYPE_1__ drpath; scalar_t__ lid; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IBEXIT (char*) ; 
 int /*<<< orphan*/  IB_ATTR_PORT_INFO ; 
 int /*<<< orphan*/  IB_PORT_LID_F ; 
 int /*<<< orphan*/  IB_PORT_LOCAL_PORT_F ; 
 int /*<<< orphan*/  buf ; 
 scalar_t__ ib_resolve_self_via (TYPE_2__*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mad_decode_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  smp_query_via (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcport ; 

int get_peer(ib_portid_t* portid, int outport, int* peerlid, int* peerport)
{
	ib_portid_t selfportid = { 0 };
	ib_portid_t peerportid = { 0 };
	int selfport = 0;

	/* set peerportid for peer port */
	memcpy(&peerportid, portid, sizeof(peerportid));
	peerportid.drpath.cnt = 1;
	peerportid.drpath.p[1] = outport;
	if (ib_resolve_self_via(&selfportid, &selfport, 0, srcport) < 0)
		IBEXIT("failed to resolve self portid");
	peerportid.drpath.drslid = (uint16_t) selfportid.lid;
	peerportid.drpath.drdlid = 0xffff;
	if (!smp_query_via(buf, &peerportid, IB_ATTR_PORT_INFO, 0, 0, srcport))
		IBEXIT("get peer portinfo failed - unable to configure lossy\n");

	mad_decode_field(buf, IB_PORT_LID_F, peerlid);
	mad_decode_field(buf, IB_PORT_LOCAL_PORT_F, peerport);

	return 0;
}