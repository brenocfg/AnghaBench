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
typedef  int /*<<< orphan*/  st_data_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_node_hash; TYPE_1__* p_subn; } ;
typedef  TYPE_2__ osm_qos_policy_t ;
struct TYPE_7__ {scalar_t__ print_desc; int /*<<< orphan*/  map_item; } ;
typedef  TYPE_3__ osm_node_t ;
typedef  int /*<<< orphan*/  cl_qmap_t ;
struct TYPE_5__ {int /*<<< orphan*/  node_guid_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_qmap_count (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_head (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st_init_strtable () ; 
 int /*<<< orphan*/  st_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__build_nodebyname_hash(osm_qos_policy_t * p_qos_policy)
{
	osm_node_t * p_node;
	cl_qmap_t  * p_node_guid_tbl = &p_qos_policy->p_subn->node_guid_tbl;

	p_qos_policy->p_node_hash = st_init_strtable();
	CL_ASSERT(p_qos_policy->p_node_hash);

	if (!p_node_guid_tbl || !cl_qmap_count(p_node_guid_tbl))
		return;

	for (p_node = (osm_node_t *) cl_qmap_head(p_node_guid_tbl);
	     p_node != (osm_node_t *) cl_qmap_end(p_node_guid_tbl);
	     p_node = (osm_node_t *) cl_qmap_next(&p_node->map_item)) {
		if (!st_lookup(p_qos_policy->p_node_hash,
			      (st_data_t)p_node->print_desc, NULL))
			st_insert(p_qos_policy->p_node_hash,
				  (st_data_t)p_node->print_desc,
				  (st_data_t)p_node);
	}
}