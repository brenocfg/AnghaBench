#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_7__* port; int /*<<< orphan*/  mcm_port_tbl; } ;
typedef  TYPE_1__ osm_mgrp_t ;
struct TYPE_11__ {int /*<<< orphan*/  mgrp_list; } ;
typedef  TYPE_2__ osm_mgrp_box_t ;
typedef  TYPE_1__ osm_mcm_port_t ;
struct TYPE_12__ {int /*<<< orphan*/  map_item; int /*<<< orphan*/  list_item; } ;
typedef  TYPE_4__ osm_mcast_work_obj_t ;
typedef  int /*<<< orphan*/  cl_qmap_t ;
typedef  int /*<<< orphan*/  cl_qlist_t ;
typedef  int /*<<< orphan*/  cl_map_item_t ;
typedef  int /*<<< orphan*/  cl_list_item_t ;
struct TYPE_13__ {int /*<<< orphan*/  guid; } ;

/* Variables and functions */
 TYPE_1__* cl_item_obj (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qlist_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qlist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qlist_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qlist_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qlist_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_qmap_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qmap_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qmap_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_next (int /*<<< orphan*/ *) ; 
 TYPE_4__* mcast_work_obj_new (TYPE_7__*) ; 

int osm_mcast_make_port_list_and_map(cl_qlist_t * list, cl_qmap_t * map,
				     osm_mgrp_box_t * mbox)
{
	cl_map_item_t *map_item;
	cl_list_item_t *list_item;
	osm_mgrp_t *mgrp;
	osm_mcm_port_t *mcm_port;
	osm_mcast_work_obj_t *wobj;

	cl_qmap_init(map);
	cl_qlist_init(list);

	for (list_item = cl_qlist_head(&mbox->mgrp_list);
	     list_item != cl_qlist_end(&mbox->mgrp_list);
	     list_item = cl_qlist_next(list_item)) {
		mgrp = cl_item_obj(list_item, mgrp, list_item);
		for (map_item = cl_qmap_head(&mgrp->mcm_port_tbl);
		     map_item != cl_qmap_end(&mgrp->mcm_port_tbl);
		     map_item = cl_qmap_next(map_item)) {
			/* Acquire the port object for this port guid, then
			   create the new worker object to build the list. */
			mcm_port = cl_item_obj(map_item, mcm_port, map_item);
			if (cl_qmap_get(map, mcm_port->port->guid) !=
			    cl_qmap_end(map))
				continue;
			wobj = mcast_work_obj_new(mcm_port->port);
			if (!wobj)
				return -1;
			cl_qlist_insert_tail(list, &wobj->list_item);
			cl_qmap_insert(map, mcm_port->port->guid,
				       &wobj->map_item);
		}
	}
	return 0;
}