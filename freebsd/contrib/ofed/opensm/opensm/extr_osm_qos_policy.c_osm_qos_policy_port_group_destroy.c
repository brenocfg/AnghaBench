#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  port_map; int /*<<< orphan*/  map_item; struct TYPE_5__* use; struct TYPE_5__* name; } ;
typedef  TYPE_1__ osm_qos_port_t ;
typedef  TYPE_1__ osm_qos_port_group_t ;

/* Variables and functions */
 scalar_t__ cl_qmap_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_head (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qmap_remove_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void osm_qos_policy_port_group_destroy(osm_qos_port_group_t * p)
{
	osm_qos_port_t * p_port;
	osm_qos_port_t * p_old_port;

	if (!p)
		return;

	if (p->name)
		free(p->name);
	if (p->use)
		free(p->use);

	p_port = (osm_qos_port_t *) cl_qmap_head(&p->port_map);
	while (p_port != (osm_qos_port_t *) cl_qmap_end(&p->port_map))
	{
		p_old_port = p_port;
		p_port = (osm_qos_port_t *) cl_qmap_next(&p_port->map_item);
		free(p_old_port);
	}
	cl_qmap_remove_all(&p->port_map);

	free(p);
}