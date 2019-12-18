#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  guid; } ;
typedef  TYPE_1__ ibnd_port_t ;
struct TYPE_5__ {int numports; int /*<<< orphan*/  guid; TYPE_1__** ports; } ;
typedef  TYPE_2__ ibnd_node_t ;

/* Variables and functions */

__attribute__((used)) static void update_switchportguids(ibnd_node_t *node)
{
	ibnd_port_t *port;
	int p;

	for (p = 0; p <= node->numports; p++) {
		port = node->ports[p];
		if (port)
			port->guid = node->guid;
	}
}