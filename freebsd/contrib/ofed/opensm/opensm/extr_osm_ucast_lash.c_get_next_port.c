#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* node; } ;
typedef  TYPE_2__ switch_t ;
struct TYPE_7__ {scalar_t__ next_port; scalar_t__ num_ports; int* ports; } ;
typedef  TYPE_3__ link_t ;
struct TYPE_5__ {TYPE_3__** links; } ;

/* Variables and functions */

__attribute__((used)) static int get_next_port(switch_t *sw, int link)
{
	link_t *l = sw->node->links[link];
	int port = l->next_port++;

	/*
	 * note if not doing mesh analysis
	 * then num_ports is always 1
	 */
	if (l->next_port >= l->num_ports)
		l->next_port = 0;

	return l->ports[port];
}