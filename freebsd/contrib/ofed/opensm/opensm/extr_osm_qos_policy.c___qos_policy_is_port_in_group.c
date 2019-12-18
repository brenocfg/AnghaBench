#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  osm_subn_t ;
struct TYPE_3__ {int node_types; int /*<<< orphan*/  port_map; } ;
typedef  TYPE_1__ osm_qos_port_group_t ;
typedef  int /*<<< orphan*/  osm_physp_t ;
typedef  int /*<<< orphan*/  osm_node_t ;
typedef  int /*<<< orphan*/  ib_net64_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cl_ntoh64 (int /*<<< orphan*/ ) ; 
 scalar_t__ cl_qmap_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int osm_node_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * osm_physp_get_node_ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  osm_physp_get_port_guid (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static boolean_t
__qos_policy_is_port_in_group(osm_subn_t * p_subn,
			      const osm_physp_t * p_physp,
			      osm_qos_port_group_t * p_port_group)
{
	osm_node_t *p_node = osm_physp_get_node_ptr(p_physp);
	ib_net64_t port_guid = osm_physp_get_port_guid(p_physp);
	uint64_t port_guid_ho = cl_ntoh64(port_guid);

	/* check whether this port's type matches any of group's types */

	if ( p_port_group->node_types &
	     (((uint8_t)1)<<osm_node_get_type(p_node)) )
		return TRUE;

	/* check whether this port's guid is in group's port map */

	if (cl_qmap_get(&p_port_group->port_map, port_guid_ho) !=
	    cl_qmap_end(&p_port_group->port_map))
		return TRUE;

	return FALSE;
}