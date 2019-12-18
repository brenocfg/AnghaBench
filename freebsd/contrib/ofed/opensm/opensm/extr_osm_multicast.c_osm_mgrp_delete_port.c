#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_subn_t ;
typedef  int /*<<< orphan*/  osm_port_t ;
struct TYPE_10__ {int /*<<< orphan*/  mcm_alias_port_tbl; } ;
typedef  TYPE_2__ osm_mgrp_t ;
struct TYPE_11__ {TYPE_1__* p_base_mcm_port; int /*<<< orphan*/  map_item; } ;
typedef  TYPE_3__ osm_mcm_alias_guid_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
struct TYPE_12__ {int scope_state; } ;
typedef  TYPE_4__ ib_member_rec_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_9__ {int /*<<< orphan*/ * port; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ cl_qmap_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_head (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_next (int /*<<< orphan*/ *) ; 
 scalar_t__ osm_mgrp_remove_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*,TYPE_4__*) ; 

void osm_mgrp_delete_port(osm_subn_t * subn, osm_log_t * log, osm_mgrp_t * mgrp,
			  osm_port_t * port)
{
	osm_mcm_alias_guid_t *mcm_alias_guid, *next_mcm_alias_guid;
	ib_member_rec_t mcmrec;
	boolean_t mgrp_deleted = FALSE;

	next_mcm_alias_guid = (osm_mcm_alias_guid_t *) cl_qmap_head(&mgrp->mcm_alias_port_tbl);
	while (next_mcm_alias_guid != (osm_mcm_alias_guid_t *) cl_qmap_end(&mgrp->mcm_alias_port_tbl) &&
	      !mgrp_deleted) {
		mcm_alias_guid = next_mcm_alias_guid;
		next_mcm_alias_guid = (osm_mcm_alias_guid_t *) cl_qmap_next(&next_mcm_alias_guid->map_item);
		if (mcm_alias_guid->p_base_mcm_port->port == port) {
			mcmrec.scope_state = 0xf;
			mgrp_deleted = osm_mgrp_remove_port(subn, log, mgrp, mcm_alias_guid,
					     &mcmrec);
		}
	}
}