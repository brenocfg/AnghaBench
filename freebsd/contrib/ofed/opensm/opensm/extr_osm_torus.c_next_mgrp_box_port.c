#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_port_t ;
struct TYPE_7__ {int /*<<< orphan*/ * port; int /*<<< orphan*/  mcm_port_tbl; } ;
typedef  TYPE_1__ osm_mgrp_t ;
struct TYPE_8__ {int /*<<< orphan*/  mgrp_list; } ;
typedef  TYPE_2__ osm_mgrp_box_t ;
typedef  TYPE_1__ osm_mcm_port_t ;
typedef  int /*<<< orphan*/  cl_map_item_t ;
typedef  int /*<<< orphan*/  cl_list_item_t ;

/* Variables and functions */
 TYPE_1__* cl_item_obj (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_qlist_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qlist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qlist_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_item ; 
 int /*<<< orphan*/  map_item ; 

__attribute__((used)) static
osm_port_t *next_mgrp_box_port(osm_mgrp_box_t *mgb,
			       cl_list_item_t **list_iterator,
			       cl_map_item_t **map_iterator)
{
	osm_mgrp_t *mgrp;
	osm_mcm_port_t *mcm_port;
	osm_port_t *osm_port = NULL;
	cl_map_item_t *m_item = *map_iterator;
	cl_list_item_t *l_item = *list_iterator;

next_mgrp:
	if (!l_item)
		l_item = cl_qlist_head(&mgb->mgrp_list);
	if (l_item == cl_qlist_end(&mgb->mgrp_list)) {
		l_item = NULL;
		goto out;
	}
	mgrp = cl_item_obj(l_item, mgrp, list_item);

	if (!m_item)
		m_item = cl_qmap_head(&mgrp->mcm_port_tbl);
	if (m_item == cl_qmap_end(&mgrp->mcm_port_tbl)) {
		m_item = NULL;
		l_item = cl_qlist_next(l_item);
		goto next_mgrp;
	}
	mcm_port = cl_item_obj(m_item, mcm_port, map_item);
	m_item = cl_qmap_next(m_item);
	osm_port = mcm_port->port;
out:
	*list_iterator = l_item;
	*map_iterator = m_item;
	return osm_port;
}