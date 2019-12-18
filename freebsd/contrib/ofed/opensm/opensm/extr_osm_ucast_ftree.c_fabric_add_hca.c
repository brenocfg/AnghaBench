#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  node_guid; } ;
struct TYPE_11__ {TYPE_1__ node_info; } ;
typedef  TYPE_2__ osm_node_t ;
struct TYPE_12__ {int /*<<< orphan*/  map_item; } ;
typedef  TYPE_3__ ftree_hca_t ;
struct TYPE_13__ {int /*<<< orphan*/  hca_tbl; } ;
typedef  TYPE_4__ ftree_fabric_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (int) ; 
 scalar_t__ IB_NODE_TYPE_CA ; 
 int /*<<< orphan*/  cl_qmap_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* hca_create (TYPE_2__*) ; 
 scalar_t__ osm_node_get_type (TYPE_2__*) ; 

__attribute__((used)) static void fabric_add_hca(ftree_fabric_t * p_ftree, osm_node_t * p_osm_node)
{
	ftree_hca_t *p_hca;

	CL_ASSERT(osm_node_get_type(p_osm_node) == IB_NODE_TYPE_CA);

	p_hca = hca_create(p_osm_node);
	if (!p_hca)
		return;

	cl_qmap_insert(&p_ftree->hca_tbl, p_osm_node->node_info.node_guid,
		       &p_hca->map_item);
}