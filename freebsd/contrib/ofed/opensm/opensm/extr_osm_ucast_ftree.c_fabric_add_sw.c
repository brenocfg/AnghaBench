#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_7__* p_node; } ;
typedef  TYPE_2__ osm_switch_t ;
struct TYPE_12__ {scalar_t__ lid; int /*<<< orphan*/  map_item; } ;
typedef  TYPE_3__ ftree_sw_t ;
struct TYPE_13__ {scalar_t__ lft_max_lid; int /*<<< orphan*/  sw_tbl; } ;
typedef  TYPE_4__ ftree_fabric_t ;
struct TYPE_10__ {int /*<<< orphan*/  node_guid; } ;
struct TYPE_14__ {TYPE_1__ node_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (int) ; 
 scalar_t__ IB_NODE_TYPE_SWITCH ; 
 int /*<<< orphan*/  cl_qmap_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ osm_node_get_type (TYPE_7__*) ; 
 TYPE_3__* sw_create (TYPE_2__*) ; 

__attribute__((used)) static void fabric_add_sw(ftree_fabric_t * p_ftree, osm_switch_t * p_osm_sw)
{
	ftree_sw_t *p_sw;

	CL_ASSERT(osm_node_get_type(p_osm_sw->p_node) == IB_NODE_TYPE_SWITCH);

	p_sw = sw_create(p_osm_sw);
	if (!p_sw)
		return;

	cl_qmap_insert(&p_ftree->sw_tbl, p_osm_sw->p_node->node_info.node_guid,
		       &p_sw->map_item);

	/* track the max lid (in host order) that exists in the fabric */
	if (p_sw->lid > p_ftree->lft_max_lid)
		p_ftree->lft_max_lid = p_sw->lid;
}