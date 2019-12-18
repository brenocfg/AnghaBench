#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int num_ports; scalar_t__ endport_links; int /*<<< orphan*/  p_node; } ;
typedef  TYPE_3__ osm_switch_t ;
struct TYPE_10__ {TYPE_2__* p_remote_physp; } ;
typedef  TYPE_4__ osm_physp_t ;
struct TYPE_8__ {TYPE_1__* p_node; } ;
struct TYPE_7__ {int /*<<< orphan*/  sw; } ;

/* Variables and functions */
 TYPE_4__* osm_node_get_physp_ptr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sw_count_endport_links(osm_switch_t * sw)
{
	osm_physp_t *p;
	int i;

	sw->endport_links = 0;
	for (i = 1; i < sw->num_ports; i++) {
		p = osm_node_get_physp_ptr(sw->p_node, i);
		if (p && p->p_remote_physp && !p->p_remote_physp->p_node->sw)
			sw->endport_links++;
	}
}