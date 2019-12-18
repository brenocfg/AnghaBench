#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* node; } ;
typedef  TYPE_2__ ibnd_port_t ;
struct TYPE_11__ {TYPE_1__** ports; } ;
typedef  TYPE_3__ ibnd_node_t ;
struct TYPE_12__ {TYPE_3__* from_node; } ;
typedef  TYPE_4__ ibnd_fabric_t ;
struct TYPE_13__ {int cnt; size_t* p; } ;
typedef  TYPE_5__ ib_dr_path_t ;
struct TYPE_9__ {TYPE_2__* remoteport; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBND_DEBUG (char*) ; 
 int str2drpath (TYPE_5__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ibnd_port_t *ibnd_find_port_dr(ibnd_fabric_t * fabric, char *dr_str)
{
	int i = 0;
	ibnd_node_t *cur_node;
	ibnd_port_t *rc = NULL;
	ib_dr_path_t path;

	if (!fabric) {
		IBND_DEBUG("fabric parameter NULL\n");
		return NULL;
	}

	if (!dr_str) {
		IBND_DEBUG("dr_str parameter NULL\n");
		return NULL;
	}

	cur_node = fabric->from_node;

	if (str2drpath(&path, dr_str, 0, 0) == -1)
		return NULL;

	for (i = 0; i <= path.cnt; i++) {
		ibnd_port_t *remote_port = NULL;
		if (path.p[i] == 0)
			continue;
		if (!cur_node->ports)
			return NULL;

		remote_port = cur_node->ports[path.p[i]]->remoteport;
		if (!remote_port)
			return NULL;

		rc = remote_port;
		cur_node = remote_port->node;
	}

	return rc;
}