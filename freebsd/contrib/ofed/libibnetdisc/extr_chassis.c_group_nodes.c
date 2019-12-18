#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_18__ ;

/* Type definitions */
struct TYPE_24__ {int ch_found; int /*<<< orphan*/  info; struct TYPE_24__* next; TYPE_1__* chassis; struct TYPE_24__* type_next; } ;
typedef  TYPE_2__ ibnd_node_t ;
struct TYPE_25__ {TYPE_4__* chassis; TYPE_2__* nodes; TYPE_2__* switches; } ;
typedef  TYPE_3__ ibnd_fabric_t ;
struct TYPE_26__ {int nodecount; int chassisnum; struct TYPE_26__* next; } ;
typedef  TYPE_4__ ibnd_chassis_t ;
struct TYPE_27__ {TYPE_4__* first_chassis; TYPE_18__* current_chassis; int /*<<< orphan*/ * last_chassis; } ;
typedef  TYPE_5__ chassis_scan_t ;
struct TYPE_23__ {scalar_t__ chassisnum; } ;
struct TYPE_22__ {int chassisnum; int nodecount; int /*<<< orphan*/  chassisguid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_NODE_SYSTEM_GUID_F ; 
 int /*<<< orphan*/  IB_NODE_VENDORID_F ; 
 int MLX_VENDOR_ID ; 
 int VTR_VENDOR_ID ; 
 scalar_t__ add_chassis (TYPE_5__*) ; 
 int /*<<< orphan*/  add_node_to_chassis (TYPE_4__*,TYPE_2__*) ; 
 scalar_t__ build_chassis (TYPE_2__*,TYPE_18__*) ; 
 scalar_t__ fill_mellanox_chassis_record (TYPE_2__*) ; 
 scalar_t__ fill_voltaire_chassis_record (TYPE_2__*) ; 
 TYPE_4__* find_chassisguid (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  get_chassisguid (TYPE_2__*) ; 
 int /*<<< orphan*/  insert_mellanox_line_and_spine (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  is_spine (TYPE_2__*) ; 
 int mad_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mad_get_field64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int group_nodes(ibnd_fabric_t * fabric)
{
	ibnd_node_t *node;
	int chassisnum = 0;
	ibnd_chassis_t *chassis;
	ibnd_chassis_t *ch, *ch_next;
	chassis_scan_t chassis_scan;
	int vendor_id;

	chassis_scan.first_chassis = NULL;
	chassis_scan.current_chassis = NULL;
	chassis_scan.last_chassis = NULL;

	/* first pass on switches and build for every Voltaire node */
	/* an appropriate chassis record (slotnum and position) */
	/* according to internal connectivity */
	/* not very efficient but clear code so... */
	for (node = fabric->switches; node; node = node->type_next) {

		vendor_id = mad_get_field(node->info, 0,IB_NODE_VENDORID_F);

		if (vendor_id == VTR_VENDOR_ID
		    && fill_voltaire_chassis_record(node))
			goto cleanup;
		else if (vendor_id == MLX_VENDOR_ID
			&& fill_mellanox_chassis_record(node))
			goto cleanup;

	}

	/* separate every Voltaire chassis from each other and build linked list of them */
	/* algorithm: catch spine and find all surrounding nodes */
	for (node = fabric->switches; node; node = node->type_next) {
		if (mad_get_field(node->info, 0,
				  IB_NODE_VENDORID_F) != VTR_VENDOR_ID)
			continue;
		if (!node->ch_found
		    || (node->chassis && node->chassis->chassisnum)
		    || !is_spine(node))
			continue;
		if (add_chassis(&chassis_scan))
			goto cleanup;
		chassis_scan.current_chassis->chassisnum = ++chassisnum;
		if (build_chassis(node, chassis_scan.current_chassis))
			goto cleanup;
	}

	/* now make pass on nodes for chassis which are not Voltaire */
	/* grouped by common SystemImageGUID */
	for (node = fabric->nodes; node; node = node->next) {
		if (mad_get_field(node->info, 0,
				  IB_NODE_VENDORID_F) == VTR_VENDOR_ID)
			continue;
		if (mad_get_field64(node->info, 0, IB_NODE_SYSTEM_GUID_F)) {
			chassis = find_chassisguid(fabric, node);
			if (chassis)
				chassis->nodecount++;
			else {
				/* Possible new chassis */
				if (add_chassis(&chassis_scan))
					goto cleanup;
				chassis_scan.current_chassis->chassisguid =
				    get_chassisguid(node);
				chassis_scan.current_chassis->nodecount = 1;
				if (!fabric->chassis)
					fabric->chassis = chassis_scan.first_chassis;
			}
		}
	}

	/* now, make another pass to see which nodes are part of chassis */
	/* (defined as chassis->nodecount > 1) */
	for (node = fabric->nodes; node; node = node->next) {

		vendor_id = mad_get_field(node->info, 0,IB_NODE_VENDORID_F);

		if (vendor_id == VTR_VENDOR_ID)
			continue;
		if (mad_get_field64(node->info, 0, IB_NODE_SYSTEM_GUID_F)) {
			chassis = find_chassisguid(fabric, node);
			if (chassis && chassis->nodecount > 1) {
				if (!chassis->chassisnum)
					chassis->chassisnum = ++chassisnum;
				if (!node->ch_found) {
					node->ch_found = 1;
					add_node_to_chassis(chassis, node);
				}
				else if (vendor_id == MLX_VENDOR_ID){
					insert_mellanox_line_and_spine(node, chassis);
				}
			}
		}
	}

	fabric->chassis = chassis_scan.first_chassis;
	return 0;

cleanup:
	ch = chassis_scan.first_chassis;
	while (ch) {
		ch_next = ch->next;
		free(ch);
		ch = ch_next;
	}
	fabric->chassis = NULL;
	return -1;
}