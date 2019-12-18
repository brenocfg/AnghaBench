#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ib_portid_t ;
struct TYPE_3__ {int portnum; int /*<<< orphan*/  physstate; int /*<<< orphan*/  state; int /*<<< orphan*/  lid; int /*<<< orphan*/  lmc; } ;
typedef  TYPE_1__ Port ;

/* Variables and functions */
 int /*<<< orphan*/  IB_ATTR_PORT_INFO ; 
 int /*<<< orphan*/  IB_PORT_LID_F ; 
 int /*<<< orphan*/  IB_PORT_LMC_F ; 
 int /*<<< orphan*/  IB_PORT_PHYS_STATE_F ; 
 int /*<<< orphan*/  IB_PORT_STATE_F ; 
 int /*<<< orphan*/  VERBOSE (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mad_decode_field (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portid2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_query_via (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcport ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static int get_port(Port * port, int portnum, ib_portid_t * portid)
{
	char portinfo[64] = { 0 };
	void *pi = portinfo;

	port->portnum = portnum;

	if (!smp_query_via(pi, portid, IB_ATTR_PORT_INFO, portnum, timeout,
			   srcport))
		return -1;

	mad_decode_field(pi, IB_PORT_LID_F, &port->lid);
	mad_decode_field(pi, IB_PORT_LMC_F, &port->lmc);
	mad_decode_field(pi, IB_PORT_STATE_F, &port->state);
	mad_decode_field(pi, IB_PORT_PHYS_STATE_F, &port->physstate);

	VERBOSE("portid %s portnum %d: lid %d state %d physstate %d",
		portid2str(portid), portnum, port->lid, port->state,
		port->physstate);
	return 1;
}