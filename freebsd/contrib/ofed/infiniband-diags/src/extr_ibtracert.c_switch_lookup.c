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
struct TYPE_3__ {int* fdb; int linearcap; int linearFDBtop; int enhsp0; void* switchinfo; } ;
typedef  TYPE_1__ Switch ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  IB_ATTR_LINEARFORWTBL ; 
 int /*<<< orphan*/  IB_ATTR_SWITCH_INFO ; 
 int /*<<< orphan*/  IB_SW_ENHANCED_PORT0_F ; 
 int /*<<< orphan*/  IB_SW_LINEAR_FDB_CAP_F ; 
 int /*<<< orphan*/  IB_SW_LINEAR_FDB_TOP_F ; 
 int /*<<< orphan*/  mad_decode_field (void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  portid2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_query_via (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcport ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static int switch_lookup(Switch * sw, ib_portid_t * portid, int lid)
{
	void *si = sw->switchinfo, *fdb = sw->fdb;

	memset(si, 0, sizeof(sw->switchinfo));
	if (!smp_query_via(si, portid, IB_ATTR_SWITCH_INFO, 0, timeout,
			   srcport))
		return -1;

	mad_decode_field(si, IB_SW_LINEAR_FDB_CAP_F, &sw->linearcap);
	mad_decode_field(si, IB_SW_LINEAR_FDB_TOP_F, &sw->linearFDBtop);
	mad_decode_field(si, IB_SW_ENHANCED_PORT0_F, &sw->enhsp0);

	if (lid >= sw->linearcap && lid > sw->linearFDBtop)
		return -1;

	memset(fdb, 0, sizeof(sw->fdb));
	if (!smp_query_via(fdb, portid, IB_ATTR_LINEARFORWTBL, lid / 64,
			   timeout, srcport))
		return -1;

	DEBUG("portid %s: forward lid %d to port %d",
	      portid2str(portid), lid, sw->fdb[lid % 64]);
	return sw->fdb[lid % 64];
}