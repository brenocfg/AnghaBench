#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int is_mc_member; int /*<<< orphan*/  mgrp_item; int /*<<< orphan*/  p_node; int /*<<< orphan*/  num_of_mcm; } ;
typedef  TYPE_5__ osm_switch_t ;
struct TYPE_15__ {TYPE_4__* p_physp; TYPE_1__* p_node; } ;
typedef  TYPE_6__ osm_port_t ;
struct TYPE_16__ {TYPE_6__* p_port; } ;
typedef  TYPE_7__ osm_mcast_work_obj_t ;
typedef  int /*<<< orphan*/  ib_net64_t ;
typedef  int /*<<< orphan*/  cl_qmap_t ;
typedef  int /*<<< orphan*/  cl_qlist_t ;
typedef  int /*<<< orphan*/  cl_list_item_t ;
struct TYPE_13__ {TYPE_3__* p_remote_physp; } ;
struct TYPE_12__ {TYPE_2__* p_node; } ;
struct TYPE_11__ {TYPE_5__* sw; } ;
struct TYPE_10__ {TYPE_5__* sw; } ;

/* Variables and functions */
 TYPE_7__* cl_item_obj (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_qlist_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qlist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qlist_next (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_qmap_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qmap_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_item ; 
 int /*<<< orphan*/  osm_node_get_node_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void create_mgrp_switch_map(cl_qmap_t * m, cl_qlist_t * port_list)
{
	osm_mcast_work_obj_t *wobj;
	osm_port_t *port;
	osm_switch_t *sw;
	ib_net64_t guid;
	cl_list_item_t *i;

	cl_qmap_init(m);
	for (i = cl_qlist_head(port_list); i != cl_qlist_end(port_list);
	     i = cl_qlist_next(i)) {
		wobj = cl_item_obj(i, wobj, list_item);
		port = wobj->p_port;
		if (port->p_node->sw) {
			sw = port->p_node->sw;
			sw->is_mc_member = 1;
		} else if (port->p_physp->p_remote_physp) {
			sw = port->p_physp->p_remote_physp->p_node->sw;
			sw->num_of_mcm++;
		} else
			continue;
		guid = osm_node_get_node_guid(sw->p_node);
		if (cl_qmap_get(m, guid) == cl_qmap_end(m))
			cl_qmap_insert(m, guid, &sw->mgrp_item);
	}
}