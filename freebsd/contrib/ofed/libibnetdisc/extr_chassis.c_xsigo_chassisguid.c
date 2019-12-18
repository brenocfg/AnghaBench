#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_9__ {TYPE_3__** ports; int /*<<< orphan*/  info; } ;
typedef  TYPE_4__ ibnd_node_t ;
struct TYPE_8__ {TYPE_2__* remoteport; } ;
struct TYPE_7__ {TYPE_1__* node; } ;
struct TYPE_6__ {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_NODE_SYSTEM_GUID_F ; 
 int /*<<< orphan*/  is_xsigo_ca (int) ; 
 scalar_t__ is_xsigo_leafone (int) ; 
 scalar_t__ is_xsigo_switch (int) ; 
 int mad_get_field64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t xsigo_chassisguid(ibnd_node_t * node)
{
	uint64_t sysimgguid =
	    mad_get_field64(node->info, 0, IB_NODE_SYSTEM_GUID_F);
	uint64_t remote_sysimgguid;

	if (!is_xsigo_ca(sysimgguid)) {
		/* Byte 3 is NodeType and byte 4 is PortType */
		/* If NodeType is 1 (switch), PortType is masked */
		if (is_xsigo_switch(sysimgguid))
			return sysimgguid & 0xffffffff00ffffffULL;
		else
			return sysimgguid;
	} else {
		if (!node->ports || !node->ports[1])
			return 0;

		/* Is there a peer port ? */
		if (!node->ports[1]->remoteport)
			return sysimgguid;

		/* If peer port is Leaf 1, use its chassis GUID */
		remote_sysimgguid =
		    mad_get_field64(node->ports[1]->remoteport->node->info, 0,
				    IB_NODE_SYSTEM_GUID_F);
		if (is_xsigo_leafone(remote_sysimgguid))
			return remote_sysimgguid & 0xffffffff00ffffffULL;
		else
			return sysimgguid;
	}
}