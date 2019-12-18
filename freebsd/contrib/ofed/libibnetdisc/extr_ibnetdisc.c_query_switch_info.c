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
typedef  int /*<<< orphan*/  smp_engine_t ;
struct TYPE_4__ {scalar_t__ smaenhsp0; } ;
typedef  TYPE_1__ ibnd_node_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IB_ATTR_SWITCH_INFO ; 
 int issue_smp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  recv_switch_info ; 

__attribute__((used)) static int query_switch_info(smp_engine_t * engine, ib_portid_t * portid,
			     ibnd_node_t * node)
{
	node->smaenhsp0 = 0;	/* assume base SP0 */
	return issue_smp(engine, portid, IB_ATTR_SWITCH_INFO, 0,
			 recv_switch_info, node);
}