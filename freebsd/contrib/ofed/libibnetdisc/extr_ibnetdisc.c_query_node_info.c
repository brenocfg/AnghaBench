#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ni_cbdata {int dummy; } ;
typedef  int /*<<< orphan*/  smp_engine_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IBND_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IB_ATTR_NODE_INFO ; 
 int issue_smp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  portid2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recv_node_info ; 

__attribute__((used)) static int query_node_info(smp_engine_t * engine, ib_portid_t * portid,
			   struct ni_cbdata * cbdata)
{
	IBND_DEBUG("Query Node Info; %s\n", portid2str(portid));
	return issue_smp(engine, portid, IB_ATTR_NODE_INFO, 0,
			 recv_node_info, (void *)cbdata);
}