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
struct TYPE_10__ {int portnum; TYPE_1__* remoteport; } ;
typedef  TYPE_2__ ibnd_port_t ;
struct TYPE_11__ {int numports; int /*<<< orphan*/  ch_found; TYPE_2__** ports; } ;
typedef  TYPE_3__ ibnd_node_t ;
struct TYPE_12__ {TYPE_3__** spinenode; } ;
typedef  TYPE_4__ ibnd_chassis_t ;
struct TYPE_9__ {TYPE_3__* node; } ;

/* Variables and functions */
 int SPINES_MAX_NUM ; 
 scalar_t__ insert_line_router (TYPE_3__*,TYPE_4__*) ; 
 int is_spine_4700x2 (TYPE_3__*) ; 

__attribute__((used)) static int pass_on_spines_catch_lines(ibnd_chassis_t * chassis)
{
	ibnd_node_t *node, *remnode;
	ibnd_port_t *port;
	int i, p;

	for (i = 1; i <= SPINES_MAX_NUM; i++) {
		int is_4700x2;

		node = chassis->spinenode[i];
		if (!node)
			continue;	/* empty slot */

		is_4700x2 = is_spine_4700x2(node);

		for (p = 1; p <= node->numports; p++) {
			port = node->ports[p];
			if (!port || !port->remoteport)
				continue;

			/*
			 * ISR4700 double density fabric board ports 19-36 are
			 * chassis external ports, so skip them
			 */
			if (is_4700x2 && (port->portnum > 18))
				continue;

			remnode = port->remoteport->node;

			if (!remnode->ch_found)
				continue;	/* some error - line/router not initialized ? FIXME */

			if (insert_line_router(remnode, chassis))
				return -1;
		}
	}
	return 0;
}