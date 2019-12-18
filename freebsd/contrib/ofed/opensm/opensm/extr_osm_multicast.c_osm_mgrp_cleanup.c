#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_3__* p_osm; int /*<<< orphan*/ ** mboxes; int /*<<< orphan*/  mgrp_mgid_tbl; } ;
typedef  TYPE_4__ osm_subn_t ;
struct TYPE_21__ {int /*<<< orphan*/  mlid; int /*<<< orphan*/  list_item; int /*<<< orphan*/  map_item; scalar_t__ well_known; int /*<<< orphan*/  mcm_port_tbl; int /*<<< orphan*/  mcm_alias_port_tbl; scalar_t__ full_members; } ;
typedef  TYPE_5__ osm_mgrp_t ;
struct TYPE_22__ {int /*<<< orphan*/  mgrp_list; } ;
typedef  TYPE_6__ osm_mgrp_box_t ;
struct TYPE_23__ {int /*<<< orphan*/  list_item; TYPE_1__* port; int /*<<< orphan*/  map_item; } ;
typedef  TYPE_7__ osm_mcm_port_t ;
struct TYPE_24__ {int /*<<< orphan*/  map_item; } ;
typedef  TYPE_8__ osm_mcm_alias_guid_t ;
struct TYPE_18__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_19__ {TYPE_2__ sa; } ;
struct TYPE_17__ {int /*<<< orphan*/  mcm_list; } ;

/* Variables and functions */
 size_t IB_LID_MCAST_START_HO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cl_fmap_remove_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cl_is_qlist_empty (int /*<<< orphan*/ *) ; 
 size_t cl_ntoh16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_qlist_remove_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_count (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qmap_remove_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int /*<<< orphan*/  mgrp_box_delete (TYPE_6__*) ; 
 TYPE_6__* osm_get_mbox_by_mlid (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_mcm_alias_guid_delete (TYPE_8__**) ; 
 int /*<<< orphan*/  osm_mcm_port_delete (TYPE_7__*) ; 

void osm_mgrp_cleanup(osm_subn_t * subn, osm_mgrp_t * mgrp)
{
	osm_mgrp_box_t *mbox;
	osm_mcm_alias_guid_t *mcm_alias_guid;
	osm_mcm_port_t *mcm_port;

	if (mgrp->full_members)
		return;

	while (cl_qmap_count(&mgrp->mcm_alias_port_tbl)) {
		mcm_alias_guid = (osm_mcm_alias_guid_t *) cl_qmap_head(&mgrp->mcm_alias_port_tbl);
		cl_qmap_remove_item(&mgrp->mcm_alias_port_tbl, &mcm_alias_guid->map_item);
		osm_mcm_alias_guid_delete(&mcm_alias_guid);
	}

	while (cl_qmap_count(&mgrp->mcm_port_tbl)) {
		mcm_port = (osm_mcm_port_t *) cl_qmap_head(&mgrp->mcm_port_tbl);
		cl_qmap_remove_item(&mgrp->mcm_port_tbl, &mcm_port->map_item);
		cl_qlist_remove_item(&mcm_port->port->mcm_list,
				     &mcm_port->list_item);
		osm_mcm_port_delete(mcm_port);
	}

	if (mgrp->well_known)
		return;

	cl_fmap_remove_item(&subn->mgrp_mgid_tbl, &mgrp->map_item);

	mbox = osm_get_mbox_by_mlid(subn, mgrp->mlid);
	cl_qlist_remove_item(&mbox->mgrp_list, &mgrp->list_item);
	if (cl_is_qlist_empty(&mbox->mgrp_list)) {
		subn->mboxes[cl_ntoh16(mgrp->mlid) - IB_LID_MCAST_START_HO] = NULL;
		mgrp_box_delete(mbox);
	}
	free(mgrp);

	subn->p_osm->sa.dirty = TRUE;
}