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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IBEXIT (char*) ; 
 int /*<<< orphan*/  IB_ATTR_NODE_INFO ; 
 int IB_NODE_SWITCH ; 
 int /*<<< orphan*/  IB_NODE_TYPE_F ; 
 int mad_get_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_query_via (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcport ; 

__attribute__((used)) static int get_node_info(ib_portid_t * dest, uint8_t * data)
{
	int node_type;

	if (!smp_query_via(data, dest, IB_ATTR_NODE_INFO, 0, 0, srcport))
		IBEXIT("smp query nodeinfo failed");

	node_type = mad_get_field(data, 0, IB_NODE_TYPE_F);
	if (node_type == IB_NODE_SWITCH)	/* Switch NodeType ? */
		return 1;
	else
		return 0;
}